namespace Storm;
using SDL3;

public partial class SRP {
  public abstract class RenderPass {
    private bool   active;
    private IntPtr rp;

    public int index;
    public SRP? srp;

    public RenderPass? Previous { get => srp[index - 1]; }

    public RenderPass() {
      active = false;
      rp     = 0;
      index  = 0;
      srp    = null;
    }

    protected void Begin (in List<RenderTarget>? targets) {
      // first check if the previous stage's pass can be recycled
      // if yes, just copy, if not, end previous, and begin a new one
      // Construct target infos, including load/store ops and clear color
      // unless the target has one specified
    }

    protected void End (bool force = false) {
      // Only end if this is the last stage
      // if force is true, just end the pas
    }

    /// <summary>
    /// A function called by an SRP to record render passes and gpu calls.
    /// </summary>
    /// <param name="sources">An optional list of source render targets provided
    /// by the previous render stage</param> <param name="targets">A required
    /// list of output render targets to be passed to the next stage</param>
    public abstract void Record (List<RenderTarget>? sources,
      out List<RenderTarget>? targets);
  }
}