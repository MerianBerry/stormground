namespace Storm;
using SDL3;

public partial class SRP {
  private class PipelineSubscription : Window.Subscription {
    private IntPtr                            ffence = 0;
    private uint                              lastW, lastH;
    private RenderTarget                      primaryTarget = new();
    private RenderTarget                      primaryDepth  = new();
    private RenderTarget                      swap          = new();
    private SDL.SDL_GPUViewport               viewport      = new();
    private SDL.SDL_FColor                    ccolor        = new();
    private SDL.SDL_GPUColorTargetInfo        ctinfo        = new();
    private SDL.SDL_GPUDepthStencilTargetInfo dstinfo       = new();

    public override void Update() {
      IntPtr cmd = SDL.SDL_AcquireGPUCommandBuffer (target.SRP.device);
      IntPtr swapTex;
      uint   swapW;
      uint   swapH;
      bool   outOfDate = false;

      Span<IntPtr> fences = [ffence];

      if (ffence != 0) {
        SDL.SDL_WaitForGPUFences (target.SRP.device,
          true,
          fences,
          (uint)fences.Length);
        foreach (var fence in fences) {
          SDL.SDL_ReleaseGPUFence (target.SRP.device, fence);
        }
      }

      SDL.SDL_WaitAndAcquireGPUSwapchainTexture (cmd,
        target.Handle,
        out swapTex,
        out swapW,
        out swapH);
      outOfDate = lastW != swapW || lastH != swapH;

      if (!swap) {
        swap = new(target.SRP,
          swapTex,
          swapW,
          swapH,
          SDL.SDL_GetGPUSwapchainTextureFormat (target.SRP.device,
            target.Handle),
          SDL.SDL_GPUTextureUsageFlags.SDL_GPU_TEXTUREUSAGE_COLOR_TARGET);
      }

      List<RenderTarget>? renderTargets = null;
      foreach (RenderPass pass in target.SRP.primaryPasses) {
        pass.Record (renderTargets, out renderTargets);
      }

      if (!primaryTarget || outOfDate) {
        if (primaryTarget) {
          primaryTarget.Release();
        }
        primaryTarget = new(target.SRP,
          swapW,
          swapH,
          swap.Format,
          SDL.SDL_GPUTextureUsageFlags.SDL_GPU_TEXTUREUSAGE_COLOR_TARGET);
      }

      if (!primaryDepth || outOfDate) {
        if (primaryDepth) {
          primaryDepth.Release();
        }
        primaryDepth = new(target.SRP,
          swapW,
          swapH,
          SDL.SDL_GPUTextureFormat.SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT,
          SDL.SDL_GPUTextureUsageFlags
            .SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET);
      }
      lastW = swapW;
      lastH = swapH;

      ctinfo.clear_color = ccolor;
      ctinfo.texture     = swapTex;
      ctinfo.load_op     = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_CLEAR;
      ctinfo.store_op    = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_STORE;
      Span<SDL.SDL_GPUColorTargetInfo> cinfos = [ctinfo];

      dstinfo.clear_depth      = 0.0F;
      dstinfo.clear_stencil    = 1;
      dstinfo.texture          = primaryDepth.Texture;
      dstinfo.stencil_load_op  = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_CLEAR;
      dstinfo.stencil_store_op = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_STORE;
      dstinfo.load_op          = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_CLEAR;
      dstinfo.store_op         = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_STORE;

      IntPtr rp =
        SDL.SDL_BeginGPURenderPass (cmd, cinfos, (uint)cinfos.Length, dstinfo);
      viewport.x = 0;
      viewport.y = 0;
      viewport.w = swapW;
      viewport.h = swapH;
      SDL.SDL_SetGPUViewport (rp, viewport);
      SDL.SDL_EndGPURenderPass (rp);
      ffence = SDL.SDL_SubmitGPUCommandBufferAndAcquireFence (cmd);
      cinfos.Clear();
    }
  }
}