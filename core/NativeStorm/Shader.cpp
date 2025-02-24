#include "native.hpp"

#include "SDL3/SDL_shadercross.h"

STORMAPI void Storm_InitShaderCompiler() {
  if (SDL_ShaderCross_Init()) {
    Storm_LogInfo ("NativeShader", "Initialized SDL_shadercross");
  }
}

STORMAPI void Storm_QuitShaderCompiler() {
  SDL_ShaderCross_Quit();
}

/* Compiles an hlsl source file into a spirv binary form
  and writes it to `out`.
 */
STORMAPI int Storm_CompileShader (char const* file, char const* out) {
  // TODO:
  // Determine shader stage via custom pragma
  // Determine entry point name via custom pragma
  // Load and read file
  // Set include dir to the parent dir of the file
  // Insert shader stage as 4 bytes at the start of the bytecode
  // (3 to confirm, 1 for actual information)

  SDL_ShaderCross_HLSL_Info info;
}

/* Loads spirv binary code, and turns it into an sdl compatible shader object
 */
STORMAPI SDL_GPUShader* Storm_LoadShader (SDL_GPUDevice* dev,
  SDL_GPUShaderFormat format, uint8_t const* code, int size) {
  // TODO:
  // Confirm and skip sg magic number and shader stage
  // Get reflection metadata from spirv
  // Transcompile spriv into the requested format code
  // Create graphics shader

  code += 4;
  size -= 4;
  SDL_ShaderCross_GraphicsShaderMetadata meta;
  SDL_ShaderCross_ReflectGraphicsSPIRV (code, size, &meta);
}

/*#include "slang/include/slang.h"
#include "slang/include/slang-com-ptr.h"
#include "SDL3/SDL_gpu.h"

using namespace Slang;
using namespace slang;*/

/*STORMAPI void* Storm_CreateShaderSession (SDL_GPUShaderFormat format) {
  ComPtr<IGlobalSession> G;
  SlangResult            r = createGlobalSession (G.writeRef());
  if (!r)
    Storm_LogInfo ("NativeShader", "Created global slang session");
  else {
    Storm_LogError ("NativeShader", "Failed to create global session");
    return NULL;
  }

  SlangCompileTarget slformat;
  std::string        vt = "";
  std::string        pt = "";
  switch (format) {
  case SDL_GPU_SHADERFORMAT_DXIL:
    slformat = SLANG_DXIL;
    vt       = "vs_6_0";
    pt       = "ps_6_0";
    break;
  case SDL_GPU_SHADERFORMAT_SPIRV:
    slformat = SLANG_SPIRV;
    vt       = "spriv_1_5";
    pt       = "spirv_1_5";
    break;
  default:
    slformat = SLANG_TARGET_UNKNOWN;
    break;
  }
  if (slformat == SLANG_TARGET_UNKNOWN) {
    return Storm_LogError ("NativeShader", "Unknown shader format"), nullptr;
  }

  SessionDesc desc = {};

  TargetDesc vsTargetDesc = {};
  vsTargetDesc.format     = slformat;
  vsTargetDesc.profile    = G->findProfile (vt.c_str());

  TargetDesc psTargetDesc = {};
  psTargetDesc.format     = slformat;
  psTargetDesc.profile    = G->findProfile (pt.c_str());

  TargetDesc targets[] = {vsTargetDesc, psTargetDesc};
  desc.targets         = targets;
  desc.targetCount     = sizeof (targets) / sizeof (targets[0]);

  std::vector<CompilerOptionEntry> options = {};
  desc.compilerOptionEntries               = options.data();
  desc.compilerOptionEntryCount            = options.size();

  ComPtr<ISession> session;
  r = G->createSession (desc, session.writeRef());
  if (r)
    return Storm_LogError ("NativeShader", "Failed to create slang session"),
           nullptr;
  else
    return Storm_LogInfo ("NativeShader", "Created slang session"), G.detach(),
           session.detach();
}

STORMAPI void* Storm_CompileShader (ISession* session, char const* name,
  char const* code) {
  IModule* module = nullptr;
  {
    ComPtr<IBlob> diagnostics;
    module = session->loadModuleFromSourceString (name,
      name,
      code,
      diagnostics.writeRef());
    if (!module) {
      Storm_LogError ("NativeShader",
        (char const*)diagnostics->getBufferPointer());
      return NULL;
    }
  }

  ComPtr<IEntryPoint> VMain;
  SlangResult r = module->findEntryPointByName ("VMain", VMain.writeRef());
  if (r) {
    Storm_LogError ("NativeShader", "Couldn't find VMain entry point");
    return NULL;
  }

  ComPtr<IEntryPoint> FMain;
  r = module->findEntryPointByName ("FMain", FMain.writeRef());
  if (r) {
    Storm_LogError ("NativeShader", "Couldn't find FMain entry point");
    return NULL;
  }

  std::vector<IComponentType*> componentTypes = {
    module,
    VMain,
    FMain,
  };

  ComPtr<IComponentType> program;
  {
    ComPtr<IBlob> diagnostics;
    r = session->createCompositeComponentType (componentTypes.data(),
      componentTypes.size(),
      program.writeRef(),
      diagnostics.writeRef());
    if (!program) {
      Storm_LogError ("NativeShader",
        (char const*)diagnostics->getBufferPointer());
      return NULL;
    }
  }

  ProgramLayout* layout = program->getLayout();

  ComPtr<IComponentType> linked;
  {
    ComPtr<IBlob> diagnostics;
    program->link (linked.writeRef(), diagnostics.writeRef());
    if (!linked) {
      Storm_LogError ("NativeShader",
        (char const*)diagnostics->getBufferPointer());
      return NULL;
    }
  }
}
*/
