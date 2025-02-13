#ifndef CoreCLR_H
#define CoreCLR_H
#include "coreclrhost.h"
#include <filesystem>
#include <initializer_list>
#include <string>
#include <vector>

class NetHost {
protected:
  using string = std::string;
  using path = std::filesystem::path;
  using directory_iterator = std::filesystem::directory_iterator;
  using recursive_directory_iterator =
      std::filesystem::recursive_directory_iterator;

private:
  path coreclr;
  path netruntime;
  void *lib = NULL;
  coreclr_initialize_ptr coreclr_initialize = NULL;
  coreclr_create_delegate_ptr coreclr_create_delegate = NULL;
  coreclr_shutdown_ptr coreclr_shutdown = NULL;
  void *host_handle = NULL;
  unsigned int domain_id = 0;

  int Findcoreclr();

public:
  static path ExecutableDir();

  virtual int Initialize(std::string app_domain,
                         std::vector<std::string> trusted_directories = {});
  virtual void *CreateDelegate(std::string assembly, std::string type,
                               std::string method,
                               const char *delegate_type = NULL);
  virtual ~NetHost();
};

#endif