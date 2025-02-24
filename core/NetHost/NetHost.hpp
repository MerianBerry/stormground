#ifndef CoreCLR_H
#define CoreCLR_H
#include "coreclrhost.h"
#include <filesystem>
#include <string>
#include <vector>
#include <map>

class NetException : public std::runtime_error {
 public:
  NetException (std::string msg) throw();
  virtual char const *what() const throw();
};

class NetVersion {
 protected:
  using string = std::string;
  int ParseNum (string &s);

 public:
  int major;
  int minor;
  int patch;

  NetVersion (string ver);

  bool operator>= (NetVersion const &r) {
    return (major > r.major) || (minor > r.minor && major == r.major) ||
           (patch > r.patch && major == r.major && minor == r.minor) ||
           patch == r.patch;
  }

  bool operator>= (string s) {
    NetVersion r = s;
    return *this >= r;
  }

  bool operator< (NetVersion const &r) {
    return (major < r.major) || (minor < r.minor && major == r.major) ||
           (patch < r.patch && major == r.major && minor == r.minor);
  }

  bool operator< (string s) {
    NetVersion r = s;
    return *this < r;
  }
};

class NetHost {
 protected:
  using string             = std::string;
  using path               = std::filesystem::path;
  using directory_iterator = std::filesystem::directory_iterator;
  using recursive_directory_iterator =
    std::filesystem::recursive_directory_iterator;

 private:
  path                         coreclr;
  path                         netruntime;
  bool                         bundled;
  std::map<string, path>       libs;
  void                        *lib                      = NULL;
  coreclr_initialize_ptr       coreclr_initialize       = NULL;
  coreclr_create_delegate_ptr  coreclr_create_delegate  = NULL;
  coreclr_shutdown_ptr         coreclr_shutdown         = NULL;
  coreclr_set_error_writer_ptr coreclr_set_error_writer = NULL;
  void                        *host_handle              = NULL;
  unsigned int                 domain_id                = 0;

  bool FindDotnetRuntime();
  bool Findcoreclr();


 public:
  virtual int   Initialize (std::string app_domain,
      std::vector<std::string>          trusted_directories = {});
  virtual void *CreateDelegate (std::string assembly, std::string type,
    std::string method, char const *delegate_type = NULL);
  virtual path  FindAssembly (string name);
  virtual ~NetHost();
};

#endif
