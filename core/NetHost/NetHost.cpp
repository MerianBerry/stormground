#include "NetHost.hpp"
#include "../api.hpp"
#include <cstdlib>
#include <iostream>
#include <regex>
#include "exports.hpp"

#ifdef _WIN32
#  include <Windows.h>
#  define loadlib(s)    (void *)LoadLibraryA (s)
#  define getproc(l, s) (void *)GetProcAddress ((HMODULE)l, s)
#  define freelib(l)    FreeLibrary ((HMODULE)l)
#else
#  include <dlfcn.h>
#  define loadlib(s)    (void *)dlopen (s, RTLD_LAZY)
#  define getproc(l, s) dlsym (l, s)
#  define freelib(l)    dlclose (l)

#endif

namespace fs = std::filesystem;

void Test() {
  Storm_LogInfo ("NetHost", "Test");
}

NetException::NetException (std::string msg) throw()
    : std::runtime_error (msg) {
  Storm_LogError ("NetHost", msg.c_str());
}

char const *NetException::what() const throw() {
  return std::runtime_error::what();
}

int NetVersion::ParseNum (string &s) {
  int p = 0;
  while (isdigit (s[p]))
    p++;
  int n = p;
  if (s[n] == '.')
    n++;
  auto vs = s.substr (0, p);
  s       = s.substr (n);
  return atoi (vs.c_str());
}

NetVersion::NetVersion (string ver) {
  major = ParseNum (ver);
  minor = ParseNum (ver);
  patch = ParseNum (ver);
}

static std::map<std::string, void *> PInvoked;

void const *NetHost::PInvokeOverride (char const *libName, char const *symbol) {
  if (strstr (libName, "SDL3") || strstr (libName, "Storm.Native")) {
    auto &exp = GetExports();
    auto  itr = exp.find (symbol);
    if (itr != exp.end())
      return itr->second;
    string err = "Failed to get internal symbol ";
    err += symbol;
    Storm_LogError ("NetHost", err.c_str());
    return NULL;
  } else {
    auto itr = PInvoked.find (libName);
    if (itr == PInvoked.end()) {
      void *module = loadlib (libName);
      if (!module) {
        string err = string ("Ext. Native Library ") + libName + " not found";
        Storm_LogError ("NetHost", err.c_str());
        return NULL;
      }
      // Optimize this later
      PInvoked[libName] = module;
      itr               = PInvoked.find (libName);
    }
    void *proc = getproc (itr->second, symbol);
    if (!proc) {
      string err = string ("Ext. Native Library (") + libName + ") proc (" +
                   symbol + ") does not exist";
      Storm_LogError ("NetHost", err.c_str());
      return NULL;
    }
    return proc;
  }

  return NULL;
}

bool NetHost::FindDotnetRuntime() {
  bundled = false;
  // Case for .net runtime packaged with executable
  for (auto const &i : recursive_directory_iterator (Storm_ExecutableDir())) {
    if (i.path().string().find ("coreclr.dll") != string::npos) {
      netruntime = i.path().parent_path();
      bundled    = true;
      Storm_LogInfo ("NetHost", "Found bundled .NET runtime");
      // std::cerr << "Using bundled dotnet runtime\n";
      return true;
    }
  }
#ifdef _WIN32
  string PATH = getenv ("PATH");
#else
  string PATH    = "/usr/lib/dotnet;";
#endif
  while (true) {
    auto p = PATH.find_first_of (';');
    if (p == string::npos)
      break;
    auto path = PATH.substr (0, p);
    PATH      = PATH.substr (p + 1);
    if (path.find ("dotnet") != string::npos) {
      fs::path rt = path;
      rt /= "shared/Microsoft.NETCore.App";
      std::vector<std::pair<NetVersion, fs::path>> runtimes;
      for (auto &i : directory_iterator (rt)) {
        auto       fn = i.path().filename();
        NetVersion version (fn.string());
        if (i.is_directory() && version >= "7.0.0") {
          runtimes.push_back ({version, rt / i.path().filename().string()});
        }
      }
      if (runtimes.size() == 0)
        return Storm_LogError ("NetHost", "Couldn't find valid .NET runtime"),
               false;
      NetVersion highestv ("0.0.0");
      int        highesti = 0;
      for (int i = 0; i < runtimes.size(); i++) {
        if (runtimes[i].first >= highestv) {
          highestv = runtimes[i].first;
          highesti = i;
        }
      }
      netruntime = runtimes[highesti].second;
      Storm_LogInfo ("NetHost",
        (string ("Found .NET runtime: ") + netruntime.generic_string())
          .c_str());
      return true;
    }
  }
  return false;
}

bool NetHost::Findcoreclr() {
  if (!FindDotnetRuntime())
    return false;
#ifdef _WIN32
  string CoreCLR = "coreclr.dll";
#else
  string CoreCLR = "libcoreclr.so";
#endif
  return fs::exists (netruntime / CoreCLR) ? (coreclr = netruntime / CoreCLR),
         true                              : false;
}

int NetHost::Initialize (std::string app_domain,
  std::vector<std::string>           trusted_directories) {
  if (!Findcoreclr())
    return Storm_LogError ("NetHost", "Failed to find coreclr"), 1;
  lib = loadlib (coreclr.string().c_str());
  if (!lib)
    return Storm_LogError ("NetHost", "Failed to open coreclr"), 1;


  // Get the coreclr hosting functions from the library
  coreclr_initialize =
    (coreclr_initialize_ptr)getproc (lib, "coreclr_initialize");
  coreclr_create_delegate =
    (coreclr_create_delegate_ptr)getproc (lib, "coreclr_create_delegate");
  coreclr_shutdown = (coreclr_shutdown_ptr)getproc (lib, "coreclr_shutdown");
  if (!(coreclr_initialize && coreclr_create_delegate && coreclr_shutdown)) {
    return Storm_LogError ("NetHost", "Failed to get CoreCLR delegates"), 1;
  }

  // Make the appdomain
  std::string tpa_list;
  trusted_directories.push_back (Storm_ExecutableDir().string());
  if (!bundled)
    trusted_directories.push_back (netruntime.string());
  for (auto const &dir : trusted_directories) {
    for (auto const &file : recursive_directory_iterator (dir)) {
      // Accept dll's, exclude duplicates
      string filename = file.path().filename().string();
      string path     = file.path().string();
      if (std::regex_match (filename, std::regex (".*\\.dll$")) &&
          libs.find (filename) == libs.end()) {
        // CoreCLR CANNOT handle non native separators
        // idk why its annoying
#if 1
        std::replace (path.begin() + 1, path.end(), '/', '\\');
#else
        std::replace (path.begin(), path.end(), '\\', '/');
#endif
        libs.try_emplace (filename, path);
      }
    }
  }
  // Construct the tpa list
  for (auto const &i : libs) {
    tpa_list += i.second.string() + ';';
  }
  if (tpa_list != "")
    tpa_list.erase (tpa_list.end() - 1);

  string *edir = new string (Storm_ExecutableDir().string());
  // std::replace (edir->begin(), edir->end(), '/', '\\');

  char const *property_keys[] = {
    "APP_CONTEXT_BASE_DIRECTORY",
    "TRUSTED_PLATFORM_ASSEMBLIES",
    "PINVOKE_OVERRIDE",
  };

  string override_fn =
    std::to_string ((intptr_t)(void *)NetHost::PInvokeOverride);

  char const *property_values[] = {
    edir->c_str(),
    tpa_list.c_str(),
    override_fn.c_str(),
  };

  auto &exps = GetExports();

  Storm_LogInfo ("NetHost",
    (std::to_string (exps.size()) + " internal symbols are available").c_str());

  // start the runtime
  auto f  = Storm_ExecutableDir().string();
  int  hr = coreclr_initialize (f.c_str(),
    app_domain.c_str(),
    sizeof (property_keys) / sizeof (char const *),
    property_keys,
    property_values,
    &host_handle,
    &domain_id);

  if (hr < 0) {
    std::stringstream ss;
    ss << "Failed to initialize coreclr: " << std::hex << hr;
    return Storm_LogError ("NetHost", ss.str().c_str()), 1;
  }
  Storm_LogInfo ("NetHost", "Initialized CoreCLR AppDomain");
  return 0;
}

void *NetHost::CreateDelegate (std::string assembly, std::string type,
  std::string method, char const *delegate_type) {
  if (!coreclr_create_delegate) {
    Storm_LogError ("NetHost", "NetHost isn't initialized");
    return NULL;
  }
  void *proc = NULL;
  int   hr   = coreclr_create_delegate (host_handle,
    domain_id,
    assembly.c_str(),
    type.c_str(),
    method.c_str(),
    &proc);
  if (hr < 0) {
    std::stringstream ss;
    ss << "Failed to create delegate: " << std::hex << hr;
    Storm_LogError ("NetHost", ss.str().c_str());
    return NULL;
  }
  string msg = "Created delegate: " + type + "." + method;
  Storm_LogInfo ("NetHost", msg.c_str());
  return proc;
}

fs::path NetHost::FindAssembly (string name) {
  auto const &itr = libs.find (name + ".dll");
  if (itr != libs.end())
    return itr->second;
  return "";
}

NetHost::~NetHost() {
  if (!lib)
    return;
  coreclr_shutdown (host_handle, domain_id);
  freelib (lib);
}
