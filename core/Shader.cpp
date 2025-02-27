#include "api.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include "SDL3/SDL_shadercross.h"

namespace fs = std::filesystem;
using path   = fs::path;
using string = std::string;

void Storm_InitShaderCompiler() {
  if (SDL_ShaderCross_Init()) {
    Storm_LogInfo ("NativeShader", "Initialized SDL_shadercross");
  }
}

void Storm_QuitShaderCompiler() {
  SDL_ShaderCross_Quit();
}

/* Compiles an hlsl source file into a spirv binary form
  and writes it to `out`.
 */
bool Storm_CompileShader (char const* _path, char const* out) {
  // TODO:
  // Determine shader stage via custom pragma
  // Determine entry point name via custom pragma
  // Load and read file
  // Set include dir to the parent dir of the file
  // Insert shader stage as 4 bytes at the start of the bytecode
  // (3 as magic number, 1 for actual information)
  path          file = _path;
  string        name = file.filename().string();
  std::ifstream fi (file);
  if (!fi.is_open()) {
    Storm_LogError ("NativeShader", ("Couldn't open shader " + name).c_str());
    return false;
  }
  fi.seekg (-1, std::ios_base::end);
  int len = fi.tellg();
  fi.seekg (0, std::ios_base::beg);
  char* contents = new char[len + 1];
  memset (contents, 0, (size_t)len + 1);
  fi.read (contents, len);
  fi.close();


  SDL_GPUShaderStage stage      = SDL_GPU_SHADERSTAGE_VERTEX;
  bool               foundStage = false;
  std::string        entry      = "";
  char const*        P          = contents;
  while (true) {
    P = strstr (P, "#pragma stormground ");
    if (!P)
      break;
    P += sizeof ("#pragma stormground ");
    if (!strcmp (P, "stage ")) {
      P += sizeof ("stage ");
      if (!strcmp (P, "vertex"))
        foundStage = true;
      else if (!strcmp (P, "fragment")) {
        stage      = SDL_GPU_SHADERSTAGE_FRAGMENT;
        foundStage = true;
      } else {
        Storm_LogWarn ("NativeShader", "Unknown shader stage name");
      }
    } else if (!strcmp (P, "entry ")) {
      P += sizeof ("entry ");
      while (isalnum (*P)) {
        entry += *P;
        P++;
      }
      if (entry == "") {
        Storm_LogWarn ("NativeShader",
          "No entry point name given, defaulting to \"main\"");
        entry = "main";
      }
    } else {
      Storm_LogWarn ("NativeShader", "Unknown stormground pragma");
    }
  }
  if (!foundStage) {
    Storm_LogWarn ("NativeShader",
      "Shader stage was not defined, defaulting to vertex");
  }

  SDL_ShaderCross_HLSL_Info info;

  return true;
}

/* Loads spirv binary code, and turns it into an sdl compatible shader object
 */
SDL_GPUShader* Storm_LoadShader (SDL_GPUDevice* dev, SDL_GPUShaderFormat format,
  uint8_t const* code, int size) {
  // TODO:
  // Confirm and skip sg magic number and shader stage
  // Get reflection metadata from spirv
  // Transcompile spriv into the requested format code
  // Create graphics shader

  code += 4;
  size -= 4;
  SDL_ShaderCross_GraphicsShaderMetadata meta;
  SDL_ShaderCross_ReflectGraphicsSPIRV (code, size, &meta);
  return NULL;
}
