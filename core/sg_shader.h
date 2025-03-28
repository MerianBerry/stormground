#ifndef SG_SHADER_H
#define SG_SHADER_H
#include "SDL3/SDL_gpu.h"

void sg_initShaderCompiler();

void sg_quitShaderCompiler();

int sg_compileShader (char const* _path, char const* out);

SDL_GPUShader* sg_loadShader (SDL_GPUDevice* dev, SDL_GPUShaderFormat format,
  uint8_t const* code, int size);

#endif