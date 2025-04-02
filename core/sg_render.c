#include "sg_render.h"
#include "sg_log.h"
#include <stdlib.h>

SG_RT *sg_createRT (SG *sg, SDL_GPUTextureFormat format,
  SDL_GPUTextureUsageFlags usage, SDL_GPUSampleCount samples,
  SDL_GPUTextureType type, uint32_t w, uint32_t h, uint32_t d) {
  SG_RT rt;
  memset (&rt, 0, sizeof (rt));
  rt.dev     = sg->dev;
  rt.format  = format;
  rt.usage   = usage;
  rt.samples = samples;
  rt.type    = type;
  rt.w       = w;
  rt.h       = h;
  rt.d       = d;
  SDL_GPUTextureCreateInfo info;
  memset (&info, 0, sizeof (info));
  info.format               = format;
  info.usage                = usage;
  info.sample_count         = samples;
  info.type                 = type;
  info.width                = w;
  info.height               = h;
  info.layer_count_or_depth = d;
  info.num_levels           = 1;
  if (!(rt.tex = SDL_CreateGPUTexture (sg->dev, &info))) {
    sg_logErrorf ("sg", "failed to create gpu texture: %s", SDL_GetError());
    return NULL;
  }
  SG_RT *RT = malloc (sizeof (rt));
  memcpy (RT, &rt, sizeof (rt));
  return RT;
}

void sg_releaseRT (SG_RT *rt) {
  if (rt && rt->dev && rt->tex) {
    SDL_ReleaseGPUTexture (rt->dev, rt->tex);
    free ((void *)rt);
  }
}

int sg_renderFrame (SG *sg) {
  SDL_GPUCommandBuffer *cmd = SDL_AcquireGPUCommandBuffer (sg->dev);

  if (sg->fencec) {
    SDL_WaitForGPUFences (sg->dev, 1, sg->fences, sg->fencec);
    for (int i = 0; i < sg->fencec; i++)
      SDL_ReleaseGPUFence (sg->dev, sg->fences[i]);
    sg->fencec = 0;
  }

  SDL_GPUTexture *swp;
  uint32_t        w, h;
  SDL_WaitAndAcquireGPUSwapchainTexture (cmd, sg->win, &swp, &w, &h);
  char outofdate = sg->lw < w || sg->lh < h;

  /*if (!sg->swap) {
    sg->swap = sg_create2DRT (sg,
      SDL_GetGPUSwapchainTextureFormat (sg->dev, sg->win),
      SDL_GPU_TEXTUREUSAGE_COLOR_TARGET,
      w,
      h);
  }*/

  if (!sg->depth || outofdate) {
    if (sg->depth)
      sg_releaseRT (sg->depth);
    sg->depth = sg_create2DRT (sg,
      SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT,
      SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
      w,
      h);
  }
  sg->lw = w;
  sg->lh = h;

  SDL_FColor ccolor = {
    .r = 0.f,
    .g = 0.f,
    .b = 0.f,
    .a = 1.f,
  };

  SDL_GPUColorTargetInfo cinfo;
  memset (&cinfo, 0, sizeof (cinfo));
  cinfo.clear_color               = ccolor;
  cinfo.texture                   = swp;
  cinfo.load_op                   = SDL_GPU_LOADOP_CLEAR;
  cinfo.store_op                  = SDL_GPU_STOREOP_STORE;
  SDL_GPUColorTargetInfo cinfos[] = {cinfo};

  SDL_GPUDepthStencilTargetInfo dinfo;
  memset (&dinfo, 0, sizeof (dinfo));
  dinfo.clear_depth      = 0.f;
  dinfo.clear_stencil    = 1;
  dinfo.texture          = sg->depth->tex;
  dinfo.stencil_load_op  = SDL_GPU_LOADOP_CLEAR;
  dinfo.stencil_store_op = SDL_GPU_STOREOP_STORE;
  dinfo.load_op          = SDL_GPU_LOADOP_CLEAR;
  dinfo.store_op         = SDL_GPU_STOREOP_STORE;

  SDL_GPURenderPass *rp = SDL_BeginGPURenderPass (cmd,
    &cinfo,
    sizeof (cinfos) / sizeof (cinfos[0]),
    &dinfo);
  SDL_GPUViewport    vp;
  memset (&vp, 0, sizeof (vp));
  vp.x = 0;
  vp.y = 0;
  vp.w = w;
  vp.h = h;
  SDL_SetGPUViewport (rp, &vp);
  SDL_EndGPURenderPass (rp);
  sg->fences[0] = SDL_SubmitGPUCommandBufferAndAcquireFence (cmd);
  sg->fencec++;
  return 0;
}