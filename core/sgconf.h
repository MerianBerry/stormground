#ifndef SG_CONF_H
#define SG_CONF_H

#include "sg_version.h"

#define SG_SHADER_VK   2
#define SG_SHADER_DX   8
#define SG_SHADER_MSL  16

#define SG_WORKER_SIZE 8
#define SG_MAX_DEPS    128


#ifdef _WIN32
#  define EXPORT __declspec (dllexport)
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  define SG_SHADERFORMAT SG_SHADER_DX
#elif defined(__linux__)
#  define EXPORT
#  include <unistd.h>
#  define SG_SHADERFORMAT SG_SHADER_VK
#endif

#endif