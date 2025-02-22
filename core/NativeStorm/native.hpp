#ifndef Storm_Native_H
#define Storm_Native_H
#include <string>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  define STORMAPI extern "C" __declspec (dllexport)
#endif

STORMAPI void Storm_SetError (std::string err);

#endif