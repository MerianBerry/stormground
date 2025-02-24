#ifndef CLI_HANDLER_H
#define CLI_HANDLER_H
#include <vector>
#include <string>
#include <filesystem>
#include "NetHost/NetHost.hpp"
#include "NetHost/StormProcs.hpp"

class CLIHandler {
 private:
  template <class T>
  using vector = std::vector<T>;
  using string = std::string;
  using path   = std::filesystem::path;
  using rdi    = std::filesystem::recursive_directory_iterator;

  string         command = "";
  string         target  = "";
  vector<string> args;

 public:
  int ConsumeArgs (int &argc, char **&argv, vector<string> &trustedDirs);

  int RunCommand (NetHost *host, StormProcs *procs);
};

#endif
