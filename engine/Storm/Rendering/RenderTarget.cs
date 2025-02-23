namespace Storm;
using SDL3;

public partial class SRP {
  public class RenderTarget {
    private SRP? srp;
    private IntPtr                       tex;
    private uint                         width, height, depth;
    private SDL.SDL_GPUTextureFormat     format;
    private SDL.SDL_GPUTextureUsageFlags usage;
    private SDL.SDL_GPUSampleCount       sampleCount;
    private SDL.SDL_GPUTextureType       type;

    public RenderTarget() {
      srp         = null;
      tex         = 0;
      width       = 0;
      height      = 0;
      format      = 0;
      usage       = 0;
      sampleCount = 0;
      type        = 0;
    }

    public RenderTarget (in SRP srp, IntPtr tex, uint width, uint height,
      SDL.SDL_GPUTextureFormat format, SDL.SDL_GPUTextureUsageFlags usage,
      SDL.SDL_GPUSampleCount sampleCount =
        SDL.SDL_GPUSampleCount.SDL_GPU_SAMPLECOUNT_1) {
      this.srp         = srp;
      this.tex         = tex;
      this.width       = width;
      this.height      = height;
      depth            = 1;
      this.format      = format;
      this.usage       = usage;
      this.sampleCount = sampleCount;
      type             = SDL.SDL_GPUTextureType.SDL_GPU_TEXTURETYPE_2D;
    }

    public RenderTarget (in SRP srp, uint width, uint height,
      SDL.SDL_GPUTextureFormat format, SDL.SDL_GPUTextureUsageFlags usage,
      SDL.SDL_GPUSampleCount sampleCount =
        SDL.SDL_GPUSampleCount.SDL_GPU_SAMPLECOUNT_1,
      SDL.SDL_GPUTextureType type =
        SDL.SDL_GPUTextureType.SDL_GPU_TEXTURETYPE_2D,
      uint depth = 1) {
      Update (srp, width, height, format, usage, sampleCount, type, depth);
    }

    /// <summary>
    /// Use this function to ensure that this render target is up to
    /// specification. If the existing texture is incompatible, it will be
    /// remade. Otherwise nothing happens.
    /// </summary>
    /// <param name="srp"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <param name="format"></param>
    /// <param name="usage"></param>
    /// <param name="sampleCount"></param>
    /// <param name="type"></param>
    /// <param name="depth"></param>
    /// <returns>True on success, False otherwise</returns>
    /// <exception cref="Exception"></exception>
    public bool Update (in SRP srp, uint width, uint height,
      SDL.SDL_GPUTextureFormat format =
        SDL.SDL_GPUTextureFormat.SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM_SRGB,
      SDL.SDL_GPUTextureUsageFlags usage =
        SDL.SDL_GPUTextureUsageFlags.SDL_GPU_TEXTUREUSAGE_COLOR_TARGET,
      SDL.SDL_GPUSampleCount sampleCount =
        SDL.SDL_GPUSampleCount.SDL_GPU_SAMPLECOUNT_1,
      SDL.SDL_GPUTextureType type =
        SDL.SDL_GPUTextureType.SDL_GPU_TEXTURETYPE_2D,
      uint depth = 1) {
      // Do not remake the texture if specification is identical
      if (this.width == width && this.height == height &&
          this.format == format && this.usage == usage &&
          this.sampleCount == sampleCount && this.type == type &&
          this.depth == depth)
        return true;
      Release();
      SDL.SDL_GPUTextureCreateInfo info = new() {
        width                = width,
        height               = height,
        format               = format,
        usage                = usage,
        sample_count         = sampleCount,
        type                 = type,
        layer_count_or_depth = depth,
        num_levels           = 1,
      };
      tex = SDL.SDL_CreateGPUTexture (srp.Device, info);
      if (tex == 0) {
        throw new Exception (
          "Failed to create gpu texture: " + SDL.SDL_GetError());
      }
      this.srp         = srp;
      this.width       = width;
      this.height      = height;
      this.format      = format;
      this.usage       = usage;
      this.sampleCount = sampleCount;
      this.type        = type;
      this.depth       = depth;
      return true;
    }

    public void Release() {
      if (srp != null && tex != 0)
        SDL.SDL_ReleaseGPUTexture (srp.Device, tex);
      srp         = null;
      tex         = 0;
      width       = 0;
      height      = 0;
      format      = 0;
      usage       = 0;
      sampleCount = 0;
      type        = 0;
    }

    public static implicit operator bool (RenderTarget rt) => rt.tex != 0;

    public IntPtr Texture {
      get { return tex; }
    }
    public uint Width {
      get { return width; }
    }
    public uint Height {
      get { return height; }
    }
    public SDL.SDL_GPUTextureFormat Format {
      get { return format; }
    }
  }
}