#include "NetHost.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <regex>

#ifdef _WIN32
#  include <Windows.h>
#endif

namespace fs = std::filesystem;

fs::path NetHost::ExecutableDir() {
#ifdef _WIN32
  char buf[MAX_PATH + 1];
  memset (buf, 0, sizeof (buf));
  GetModuleFileName (NULL, buf, MAX_PATH);
  fs::path ed = buf;
  return ed.parent_path();
#endif
}

int NetHost::Findcoreclr() {
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
      for (auto &i : directory_iterator (rt)) {
        auto fn = i.path().filename();
        int  mv = fn.string().c_str()[0] - '0';
        if (i.is_directory() && mv >= 8) {
          rt /= i.path().filename().string();
          for (auto &i : recursive_directory_iterator (rt)) {
            if (i.path().string().find ("coreclr.dll") !=
                string::npos) {
              coreclr    = i.path();
              netruntime = rt;
              return 0;
            }
          }
        }
      }
    }
  }
  return 1;
}

int NetHost::Initialize (std::string app_domain,
  std::vector<std::string>           trusted_directories) {
  if (Findcoreclr()) {
    return 1;
  }

  lib = LoadLibraryA (coreclr.string().c_str());
  if (!lib)
    throw std::runtime_error ("Failed to open coreclr");

  // Get the coreclr hosting functions from the library
  coreclr_initialize =
    (coreclr_initialize_ptr)GetProcAddress ((HMODULE)lib,
      "coreclr_initialize");
  coreclr_create_delegate =
    (coreclr_create_delegate_ptr)GetProcAddress ((HMODULE)lib,
      "coreclr_create_delegate");
  coreclr_shutdown =
    (coreclr_shutdown_ptr)GetProcAddress ((HMODULE)lib,
      "coreclr_shutdown");
  if (!coreclr_initialize || !coreclr_create_delegate ||
      !coreclr_shutdown) {
    throw std::runtime_error (
      std::format ("Failed to get coreclr procs: {} {} {}",
        (void *)coreclr_initialize,
        (void *)coreclr_create_delegate,
        (void *)coreclr_shutdown));
  }

  // Make the appdomain
  std::string tpa_list;
  trusted_directories.push_back (ExecutableDir().string());
  trusted_directories.push_back (netruntime.string());
  for (auto const &dir : trusted_directories) {
    for (auto const &file : directory_iterator (dir)) {
      auto name = file.path().string();
      // Accept dll's, exclude duplicates
      if (std::regex_match (name, std::regex (".*.dll$")) &&
          tpa_list.find (file.path().filename().string()) ==
            string::npos)
        tpa_list += name + ';';
    }
  }

  char const *property_keys[] = {
    "TRUSTED_PLATFORM_ASSEMBLIES",
  };
  char const *property_values[] = {
    tpa_list.c_str(),
  };

  // start the runtime
  int hr = coreclr_initialize (ExecutableDir().string().c_str(),
    app_domain.c_str(),
    sizeof (property_keys) / sizeof (char const *),
    property_keys,
    property_values,
    &host_handle,
    &domain_id);

  if (hr < 0)
    throw std::runtime_error (
      "coreclr_initialize failed with code " + std::to_string (hr));
  return 0;
}

void *NetHost::CreateDelegate (std::string assembly, std::string type,
  std::string method, char const *delegate_type) {
  if (!coreclr_create_delegate)
    throw std::runtime_error ("NetHost isnt initialized");
  void *proc = NULL;
  int   hr   = coreclr_create_delegate (host_handle,
    domain_id,
    assembly.c_str(),
    type.c_str(),
    method.c_str(),
    &proc);
  if (hr < 0) {
    std::cerr << "Failed to create delegate: " << std::hex << hr
              << std::endl;
  }
  // TODO: add error handling for failure to get proc
  return proc;
}

NetHost::~NetHost() {
  if (!lib)
    return;
  coreclr_shutdown (host_handle, domain_id);
  FreeLibrary ((HMODULE)lib);
}