namespace Storm.Core;

using System.Runtime.InteropServices;
using SDL3;

// New purpose: act like a scriptable render pipeline
// allow for queuing of render passes that get carried out during the update
// Users and stormground can put in their own render passes
// Though every srp will have a presentation rt, that is actually presented

// Simply a wrapper around a wrapper (wrapper around sdl gpu)
public partial class GPU {
  public enum Backend {
    Vulkan = 2,
    Direct3D12 = 4,
    Metal = 16,
  }
  private class Subscription : Window.Subscription {
    private IntPtr ffence = 0;
    private IntPtr deptht = 0;
    private uint lastW, lastH;

    public override void Update() {
      IntPtr cmd = SDL.SDL_AcquireGPUCommandBuffer(target.GetGPU().device);
      IntPtr swapTex;
      uint swapW;
      uint swapH;

      Span<IntPtr> fences = [ffence];

      if (ffence != 0) {
        SDL.SDL_WaitForGPUFences(target.GetGPU().device, true, fences, (uint)fences.Length);
        foreach(var fence in fences) {
          SDL.SDL_ReleaseGPUFence(target.GetGPU().device, fence);
        }
      }
      
      SDL.SDL_WaitAndAcquireGPUSwapchainTexture(cmd, target.GetHandle(), out swapTex, out swapW, out swapH);

      if (deptht == 0 || lastW != swapW || lastH != swapH) {
        if (deptht != 0) {
          SDL.SDL_ReleaseGPUTexture(target.GetGPU().device, deptht);
        }
        deptht = SDL.SDL_CreateGPUTexture(target.GetGPU().device, new SDL.SDL_GPUTextureCreateInfo() {
          format = SDL.SDL_GPUTextureFormat.SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT,
          width = swapW,
          height = swapH,
          sample_count = SDL.SDL_GPUSampleCount.SDL_GPU_SAMPLECOUNT_1,
          layer_count_or_depth = 1,
          num_levels = 1,
          type = SDL.SDL_GPUTextureType.SDL_GPU_TEXTURETYPE_2D,
          usage = SDL.SDL_GPUTextureUsageFlags.SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
        });
      }
      lastW = swapW;
      lastH = swapH;

      SDL.SDL_FColor black = new() {
        r = 0f,
        g = 0f,
        b = 0f,
        a = 1f
      };

      SDL.SDL_GPUColorTargetInfo swtgt = new(){
          clear_color = black,
          texture = swapTex,
          load_op = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_CLEAR,
          store_op = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_STORE,
      };
      Span<SDL.SDL_GPUColorTargetInfo> cinfos = [swtgt];
      SDL.SDL_GPUDepthStencilTargetInfo dinfo = new() {
        clear_depth = 0.0F,
        clear_stencil = 1,
        texture = deptht,
        stencil_load_op = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_DONT_CARE,
        stencil_store_op = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_DONT_CARE,
        load_op = SDL.SDL_GPULoadOp.SDL_GPU_LOADOP_DONT_CARE,
        store_op = SDL.SDL_GPUStoreOp.SDL_GPU_STOREOP_DONT_CARE,
      };
      IntPtr rp = SDL.SDL_BeginGPURenderPass(cmd, cinfos, (uint)cinfos.Length, dinfo);
      SDL.SDL_SetGPUViewport(rp, new() {
        x = 0,
        y = 0,
        w = swapW,
        h = swapH,
      });
      SDL.SDL_EndGPURenderPass(rp);
      ffence = SDL.SDL_SubmitGPUCommandBufferAndAcquireFence(cmd);
      
    }
  }

  private  Window? window;
  private IntPtr device;

  public GPU(in Window window, bool debugging = true) {
    this.window = window;
    device = 0;
    foreach(Backend b in Main.backendPriority) {
      SDL.SDL_GPUShaderFormat format = (SDL.SDL_GPUShaderFormat)b;
      bool sup = SDL.SDL_GPUSupportsShaderFormats(format, null);
      if (sup) {
        device = SDL.SDL_CreateGPUDevice(format, debugging, null);
        if (device == 0) {
          throw new Exception("Couldn't make gpu device: " + SDL.SDL_GetError());
        }
        break;
      }
    }
    if (device == 0)
      throw new Exception("Couldn't select any graphics backend");
    SDL.SDL_ClaimWindowForGPUDevice(device, window.GetHandle());
    
    window.Subscribe<Subscription>();
  }
}