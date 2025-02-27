#include <vector>
#include <filesystem>

#include "api.hpp"
#include "NetHost/StormProcs.hpp"
#include "NetHost/NetHost.hpp"
#include "CLIHandler.hpp"


DLLEXPORT char const* WHAT =
  "sg#############################################################";


#ifdef _WIN32
#  include <Windows.h>
#endif

int main (int argc, char** argv) {
  namespace fs      = std::filesystem;
  NetHost* host     = new NetHost;
  fs::path execname = Storm_ExecutablePath().filename().replace_extension();
  argc--;
  argv++;

  Storm_LogInfo ("Core", "Program has started");

  std::vector<std::string> trustedDirs = {};
  std::string              target      = execname.string();

  CLIHandler* ci = new CLIHandler();

  if (ci->ConsumeArgs (argc, argv, trustedDirs))
    return 1;

  if (host->Initialize (target, trustedDirs)) {
    return Storm_LogError ("sg", "Failed to initialize host, quitting"), 1;
  }

  StormProcs* procs;
  try {
    procs = new StormProcs (host);
  } catch (NetException e) {
    return 1;
  }

  ci->RunCommand (host, procs);

  Storm_LogInfo ("Core", "Engine has exited");

  delete ci;
  delete procs;
  delete host;
  return 0;
}
