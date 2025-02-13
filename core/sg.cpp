#include <vector>
#include <filesystem>
#include <iostream>
#include <string.h>

#include "SDL3/SDL.h"

#include "NetHost/NetHost.hpp"


using EntryFromCore_fn = void (*) (char const*);

int main (int argc, char** argv) {
  namespace fs                  = std::filesystem;
  NetHost*                 host = new NetHost;
  std::vector<std::string> debugdirs;
  if (argc > 1 && !strcmp (argv[1], "debug")) {
    std::vector<fs::path> searches = {
      std::filesystem::current_path()};
    argc -= 2;
    if (argc > 0) {
      for (int i = 2; argc > 0; --argc, ++i) {
        searches.push_back (std::string (argv[i]));
      }
    }
    std::cerr << "Starting in debug mode\n";
    for (auto const& search : searches) {
      for (auto const& dir :
        std::filesystem::recursive_directory_iterator (search)) {
        if (dir.is_directory() && dir.path().filename() == "Debug" &&
            dir.path().parent_path().filename() == "bin") {
          debugdirs.push_back (dir.path().string());
        }
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
  if (!EntryFromCore) {
    throw std::runtime_error ("Couldn't find EntryFromCore... fatal");
  }

  // if (!SDL_Init (SDL_INIT_VIDEO)) {
  //   return 1;
  // }

  EntryFromCore (NetHost::ExecutableDir().string().c_str());

  delete host;
  return 0;
}
