#include "CLIHandler.hpp"
#include "NativeStorm/native.hpp"
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
      return 0;
    } else {
      string err = "Unknown CLI command: ";
      err += cmd;
      return Storm_LogError ("CLIHandler", err.c_str()), 1;
    }
  }
  return 0;
}

int CLIHandler::RunCommand (NetHost *host, StormProcs *procs) {
  if (command == "debug") {
    fs::path usrdll = host->FindAssembly (target);

    procs->EntryFromCore (Storm_ExecutableDir().string().c_str(),
      usrdll.string().c_str());
  }
  return 0;
}
