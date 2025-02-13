#include <vector>
#include <filesystem>
#include <iostream>
#include <string.h>

#include "NetHost/NetHost.hpp"


extern char const mobdebug_lua[];
extern char const socket_lua[];

#ifdef SG_INCLUDE_GENERATED
#  include "mobdebug.h"
#  include "socket.h"
#else
#endif

using EntryFromCore_fn = void (*)();

int main (int argc, char** argv) {
  // int                  r         = sg_handleArgs (argc, argv);
  namespace fs                  = std::filesystem;
  NetHost*                 host = new NetHost;
  std::vector<std::string> debugdirs;
  if (argc > 1 && !strcmp (argv[1], "debug")) {
    std::cerr << "Starting in debug mode\n";
    for (auto const& dir :
      std::filesystem::recursive_directory_iterator (
        std::filesystem::current_path())) {
      if (dir.is_directory() && dir.path().filename() == "Debug" &&
          dir.path().parent_path().filename() == "bin") {
        debugdirs.push_back (dir.path().string());
      }
    }
    for (auto& i : debugdirs) {
      std::cerr << "Debug dir: " << i << std::endl;
    }
  }
  host->Initialize ("sg", debugdirs);
  EntryFromCore_fn EntryFromCore = NULL;
  EntryFromCore = (EntryFromCore_fn)host->CreateDelegate ("SG.Core",
    "SG.Core.Main",
    "EntryFromCore");
  if (EntryFromCore) {
    EntryFromCore();
  }
}
