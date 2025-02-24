namespace Storm;

public class DefaultRenderPass : SRP.RenderPass {
  private SRP.RenderTarget monitor = new();

  public override void Record (List<SRP.RenderTarget>? sources,
    out List<SRP.RenderTarget>? targets) {
    targets = null;
    if (srp == null)
      return;
    monitor.Update (srp, 160, 96);
    targets = [monitor];
    Begin (targets);

    End();
  }
}
