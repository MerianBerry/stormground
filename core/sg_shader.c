#include <ctype.h>
#include "SDL3/SDL_shadercross.h"
#include "scl.h"

void sg_initShaderCompiler() {
  if (SDL_ShaderCross_Init()) {
    // Storm_LogInfo ("NativeShader", "Initialized SDL_shadercross");
  }
}

void sg_quitShaderCompiler() {
  SDL_ShaderCross_Quit();
}

/* Compiles an hlsl source file into a spirv binary form
  and writes it to `out`.
 */
int sg_compileShader (char const* _path, char const* out) {
  // TODO:
  // Load and read file
  // Determine stage entrypoints via custom pragmas
  // Set include dir to the parent dir of the file
  // Compile all specified or implied entrypoints
  // Insert shader stage as 4 bytes at the start of the spirv
  // (3 as magic number, 1 for actual information)
  scl_file* F = scl_open ("rb", _path);
  if (!F) {
    return 0;
  }
  char* contents;
  scl_read_malloc (F, (void**)&contents, -1);
  if (!contents) {
    return 0;
  }
  scl_close (F);


  SDL_GPUShaderStage stage      = SDL_GPU_SHADERSTAGE_VERTEX;
  bool               foundStage = false;
  char const*        entry      = "";
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
        // Storm_LogWarn ("NativeShader", "Unknown shader stage name");
      }
    } else if (!strcmp (P, "entry ")) {
      P += sizeof ("entry ");
      while (isalnum (*P)) {
        entry += *P;
        P++;
      }
      if (!strcmp (entry, "")) {
        /*Storm_LogWarn ("NativeShader",
          "No entry point name given, defaulting to \"main\"");*/
        entry = "main";
      }
    } else {
      // Storm_LogWarn ("NativeShader", "Unknown stormground pragma");
    }
  }
  if (!foundStage) {
    /*Storm_LogWarn ("NativeShader",
      "Shader stage was not defined, defaulting to vertex");*/
  }

  SDL_ShaderCross_HLSL_Info info;

  SDL_ShaderCross_CompileSPIRVFromHLSL (SDL_ShaderCross_HLSL_Info const* info,
    size_t*                                                              size)

    return true;
}

/* Loads spirv binary code, and turns it into an sdl compatible shader object
 */
SDL_GPUShader* sg_loadShader (SDL_GPUDevice* dev, SDL_GPUShaderFormat format,
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
