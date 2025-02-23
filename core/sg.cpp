#include <vector>
#include <filesystem>
#include <iostream>
#include <string.h>

#include "SDL3/SDL.h"
#include "SDL3/SDL_gpu.h"

#include "NetHost/NetHost.hpp"

#ifdef _WIN32
#  include <Windows.h>
#endif


using EntryFromCore_fn = void (*) (char const*, char const*);

int main (int argc, char** argv) {
  namespace fs  = std::filesystem;
  NetHost* host = new NetHost;
  char     buf[MAX_PATH + 1];
  memset (buf, 0, sizeof (buf));
  GetModuleFileName (NULL, buf, MAX_PATH);
  fs::path e = buf;
  fs::path n = e.filename().replace_extension();

  std::vector<std::string> debugdirs {NetHost::ExecutableDir().string()};
  std::string              dname = n.string();
  //std::cerr << "Name: " << dname << std::endl;
  if (argc > 2 && !strcmp (argv[1], "debug")) {
    std::vector<fs::path> searches = {
      std::filesystem::current_path()};
    dname = argv[2];
    argc -= 2;
    if (argc > 0) {
      for (int i = 2; argc > 0; --argc, ++i) {
        searches.push_back (std::string (argv[i]));
      }
    }
    // std::cerr << "Starting in debug mode\n";
    for (auto const& search : searches) {
      for (auto const& dir :
        std::filesystem::recursive_directory_iterator (search)) {
        if (dir.is_directory() && dir.path().filename() == "Debug" &&
            dir.path().parent_path().filename() == "bin") {
          debugdirs.push_back (dir.path().string());
        }
      }
    }
    /*for (auto& i : debugdirs) {
      std::cerr << "Debug dir: " << i << std::endl;
    }*/
  }
  // std::cerr << "User: " << dname << std::endl;

  fs::path usrdll;
  if (dname == "sg") {
    std::cerr << "No point in executing...\n";
    return 0;
  } else {
    for (auto const& dir : debugdirs) {
      if (usrdll.string() != "")
        break;
      for (auto const& i :
        std::filesystem::recursive_directory_iterator (dir)) {
        if (i.path().filename() == dname + ".dll") {
          usrdll = i.path();
          break;
        }
      }
    }
  }

  // std::cerr << "User dll: " << usrdll << std::endl;

  host->Initialize (dname, debugdirs);
  EntryFromCore_fn EntryFromCore = NULL;
  EntryFromCore = (EntryFromCore_fn)host->CreateDelegate ("Storm",
    "Storm.Core.Main",
    "EntryFromCore");
  if (!EntryFromCore) {
    throw std::runtime_error ("Couldn't find EntryFromCore... fatal");
  }

  if (!SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    return 1;
  }

  EntryFromCore (NetHost::ExecutableDir().string().c_str(),
    usrdll.string().c_str());

  SDL_Quit();

  delete host;
  return 0;
}
