#include "CLIHandler.hpp"
#include "api.hpp"
#include <regex>

namespace fs = std::filesystem;

int CLIHandler::ConsumeArgs (int &argc, char **&argv,
  vector<string> &trustedDirs) {
  if (argc > 1) {
    string cmd = argv[0];
    if (cmd == "debug") {
      command = "debug";
      argc--;
      argv++;
      vector<path> searches = {fs::current_path()};
      target                = argv[0];
      argc--;
      argv++;
      for (; argc > 0; --argc, ++argv) {
        searches.push_back (std::string (argv[0]));
      }
      for (auto const &search : searches) {
        for (auto const &dir : fs::recursive_directory_iterator (search)) {
          auto str = dir.path().generic_string();
          if (dir.is_directory() &&
              std::regex_match (str, std::regex (".*\\/bin\\/Debug$"))) {
            trustedDirs.push_back (str);
          }
        }
      }
      Storm_LogInfo ("Core", ("Starting in debug mode on " + target).c_str());
      return 0;
    } else if (cmd == "build") {
    } else {
      string err = "Unknown CLI command: ";
      err += cmd;
      return Storm_LogError ("Core", err.c_str()), 1;
    }
  }
  return 0;
}

int CLIHandler::RunCommand (NetHost *host, StormProcs *procs) {
  if (command == "debug") {
    Storm_LogInfo ("Core", "Executing debug mode with EntryFromCore");

    fs::path usrdll = host->FindAssembly (target);

    procs->BuildFromCore ("");
    auto  d   = Storm_ExecutableDir().string();
    auto  uds = usrdll.string();
    char *buf = new char[uds.length() + 1];
    memcpy (buf, uds.c_str(), uds.length() + 1);
    procs->EntryFromCore (buf);
  }
  return 0;
}
