#ifndef Storm_Native_H
#define Storm_Native_H
#include <string>
#include <filesystem>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  define STORMAPI extern "C" __declspec (dllexport)
#  define STORMDLL __declspec (dllexport)
#endif

STORMAPI void Storm_SetError (std::string err);

STORMAPI void Storm_LogInfo (char const* source, char const* msg,
  char const* trace = NULL);

STORMAPI void Storm_LogWarn (char const* source, char const* msg,
  char const* trace = NULL);

STORMAPI void Storm_LogError (char const* source, char const* msg,
  char const* trace = NULL);

STORMDLL std::filesystem::path Storm_ExecutablePath();

STORMDLL std::filesystem::path Storm_ExecutableDir();

#endif
