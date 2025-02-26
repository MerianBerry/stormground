#include "NetHost.hpp"
#include "../api.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <regex>
#include "exports.hpp"

#ifdef _WIN32
#  include <Windows.h>
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
#ifdef _WIN32
    auto &exp = GetExports();
    auto  itr = exp.find (symbol);
    if (itr != exp.end())
      return itr->second;
    string err = std::format ("Failed to get internal symbol {}: {}",
      symbol,
      GetLastError());
    Storm_LogError ("NetHost", err.c_str());
    return NULL;
#endif
  } else {
    auto itr = PInvoked.find (libName);
    if (itr == PInvoked.end()) {
#ifdef _WIN32
      HMODULE module = LoadLibraryA (libName);
      if (!module) {
        string err = std::format ("Ext. Native Library {} not found", libName);
        Storm_LogError ("NetHost", err.c_str());
        return NULL;
      }
      // Optimize this later
      PInvoked[libName] = module;
      itr               = PInvoked.find (libName);
#endif
    }
#ifdef _WIN32
    void *proc = (void *)GetProcAddress ((HMODULE)itr->second, symbol);
    if (!proc) {
      string err =
        std::format ("Ext. Native Library ({}) proc ({}) does not exist",
          libName,
          symbol);
      Storm_LogError ("NetHost", err.c_str());
      return NULL;
    }
    return proc;
#endif
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
  string PATH = getenv ("PATH");
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
  for (auto &i : recursive_directory_iterator (netruntime)) {
    if (i.path().string().find ("coreclr.dll") != string::npos) {
      coreclr = i.path();
      return true;
    }
  }
  return false;
}

int NetHost::Initialize (std::string app_domain,
  std::vector<std::string>           trusted_directories) {
  if (!Findcoreclr())
    return Storm_LogError ("NetHost", "Failed to find coreclr"), 1;
#ifdef _WIN32
  lib = LoadLibraryA (coreclr.string().c_str());
#endif
  if (!lib)
    return Storm_LogError ("NetHost", "Failed to open coreclr"), 1;

// Get the coreclr hosting functions from the library
#ifdef _WIN32
  coreclr_initialize =
    (coreclr_initialize_ptr)GetProcAddress ((HMODULE)lib, "coreclr_initialize");
  coreclr_create_delegate =
    (coreclr_create_delegate_ptr)GetProcAddress ((HMODULE)lib,
      "coreclr_create_delegate");
  coreclr_shutdown =
    (coreclr_shutdown_ptr)GetProcAddress ((HMODULE)lib, "coreclr_shutdown");
#endif
  if (!(coreclr_initialize && coreclr_create_delegate && coreclr_shutdown)) {
    string err = std::format ("Failed to get coreclr procs: {} {} {}",
      (void *)coreclr_initialize,
      (void *)coreclr_create_delegate,
      (void *)coreclr_shutdown);
    return Storm_LogError ("NetHost", err.c_str()), 1;
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
      if (std::regex_match (file.path().string(), std::regex (".*\\.dll$")) &&
          libs.find (filename) == libs.end()) {
        // CoreCLR CANNOT handle non native separators
        // idk why its annoying
#ifdef _WIN32
        std::replace (path.begin(), path.end(), '/', '\\');
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
  string *edir = new string (Storm_ExecutableDir().string());

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

  auto  &exps = GetExports();
  string msg  = std::format ("{} internal symbols are available", exps.size());
  Storm_LogInfo ("NetHost", msg.c_str());

  // start the runtime
  auto f  = Storm_ExecutablePath().string();
  int  hr = coreclr_initialize (Storm_ExecutableDir().string().c_str(),
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
  FreeLibrary ((HMODULE)lib);
}
