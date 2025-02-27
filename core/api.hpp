#ifndef Storm_API_H
#define Storm_API_H
#include <string>
#include <filesystem>
#include "SDL3/SDL.h"

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  define DLLEXPORT extern "C" __declspec(dllexport)
#else
#  include <limits.h>
#  include <unistd.h>
#  define DLLEXPORT extern "C" __attribute__ ((visibility ("default")))
#endif

void Storm_Free (void* ptr);

char const* Storm_GetError();

void Storm_SetError (std::string err);

void Storm_LogInfo (char const* source, char const* msg,
  char const* trace = NULL);

void Storm_LogWarn (char const* source, char const* msg,
  char const* trace = NULL);

void Storm_LogError (char const* source, char const* msg,
  char const* trace = NULL);

void Storm_InitShaderCompiler();

void Storm_QuitShaderCompiler();

bool Storm_CompileShader (char const* _path, char const* out);

SDL_GPUShader* Storm_LoadShader (SDL_GPUDevice* dev, SDL_GPUShaderFormat format,
  uint8_t const* code, int size);

std::filesystem::path Storm_ExecutablePath();

std::filesystem::path Storm_ExecutableDir();
#endif
