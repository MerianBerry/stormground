#include <ctype.h>
#include "SDL3/SDL_shadercross.h"
#include "scl.h"
#include "amp_shader.h"

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
int sg_compileShader (char const* path, char const* out) {
  // TODO:
  // Load and read file
  // Determine stage entrypoints via custom pragmas
  // Set include dir to the parent dir of the file
  // Compile all specified or implied entrypoints
  // Insert shader stage as 4 bytes at the start of the spirv
  // (3 as magic number, 1 for actual information)
  scl_file* F = scl_open ("rb", path);
  if (!F) {
    return 0;
  }
  char* contents;
  scl_read_malloc (F, (void**)&contents, -1);
  if (!contents) {
    return 0;
  }
  scl_close (F);
  char const* P = contents;

  struct {
    char entry[256];
    int  l;
  } stages[3];

  memset (stages, 0, sizeof (stages));

  while (true) {
    P = strstr (P, "#pragma ");
    if (!P)
      break;
    P += 9;
    if (!strcmp (P, "vertex ")) {
      P += 8;
      while (isalnum (*P) || *P == '_') {
        stages[0].entry[stages[0].l++] = *P;
        P++;
      }
    } else if (!strcmp (P, "fragment ")) {
      P += 10;
      while (isalnum (*P) || *P == '_') {
        stages[1].entry[stages[1].l++] = *P;
        P++;
      }
    }
  }
  if (!stages[0].l && !stages[1].l) {
    // sg_logWarnf ("sg", "shader %s has no entrypoints", path);
    return 1;
  }

  SDL_ShaderCross_HLSL_Info info;

  return 0;
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
