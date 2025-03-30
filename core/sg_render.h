#ifndef SG_RENDER_H
#define SG_RENDER_H

#include "sg.h"

typedef struct SG_RT {
  SDL_GPUDevice           *dev;
  SDL_GPUTexture          *tex;
  SDL_GPUTextureFormat     format;
  SDL_GPUTextureUsageFlags usage;
  SDL_GPUSampleCount       samples;
  SDL_GPUTextureType       type;
  uint32_t                 w, h, d;
} SG_RT;

SG_RT *sg_createRT (SG *sg, SDL_GPUTextureFormat format,
  SDL_GPUTextureUsageFlags usage, SDL_GPUSampleCount samples,
  SDL_GPUTextureType type, uint32_t w, uint32_t h, uint32_t d);

void sg_releaseRT (SG_RT *rt);


#define sg_create2DRT(sg, format, usage, w, h) \
  sg_createRT (sg,                             \
    format,                                    \
    usage,                                     \
    SDL_GPU_SAMPLECOUNT_1,                     \
    SDL_GPU_TEXTURETYPE_2D,                    \
    w,                                         \
    h,                                         \
    1)

int sg_renderFrame (SG *sg);

#endif