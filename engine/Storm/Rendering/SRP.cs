namespace Storm;

using System.Runtime.InteropServices;
using SDL3;

// New purpose: act like a scriptable render pipeline
// allow for queuing of render passes that get carried out during the
// update Users and stormground can put in their own render passes
// Though every srp will have a presentation rt, that is actually
// presented

// Simply a wrapper around a wrapper (wrapper around sdl gpu)
public partial class SRP {
  public enum Backend {
    Vulkan     = 2,
    Direct3D12 = 4,
    Metal      = 16,
  }

  private Window           window;
  private readonly IntPtr  device;
  private List<RenderPass> primaryPasses;

  public SRP (in Window window, bool debugging = true) {
    this.window   = window;
    device        = 0;
    primaryPasses = [];
    foreach (Backend b in Core.Main.backendPriority) {
      SDL.SDL_GPUShaderFormat format = (SDL.SDL_GPUShaderFormat)b;
      bool sup = SDL.SDL_GPUSupportsShaderFormats (format, null);
      if (sup) {
        device = SDL.SDL_CreateGPUDevice (format, debugging, null);
        if (device == 0)
          throw new Exception (
            "Couldn't make gpu device: " + SDL.SDL_GetError());
        break;
      }
    }
    if (device == 0)
      throw new Exception ("Couldn't select any graphics backend");
    SDL.SDL_ClaimWindowForGPUDevice (device, window.Handle);
    window.Subscribe<PipelineSubscription>();
    Subscribe<DefaultRenderPass>();
  }

  public void Subscribe (RenderPass rp) {
    rp.index = primaryPasses.Count;
    rp.srp   = this;
    primaryPasses.Add (rp);
  }

  public void Subscribe<T>()
    where     T : RenderPass, new() {
    T sub = new();
    Subscribe (sub);
  }

  public IntPtr Device {
    get { return device; }
  }

  public RenderPass? GetRenderPass (int index) {
    if (primaryPasses.Count == 0) {
      return null;
    }
    index = Math.Clamp (index, 0, primaryPasses.Count - 1);
    return primaryPasses[index];
  }

  public RenderPass? this[int index] {
    get => GetRenderPass (index);
  }
}