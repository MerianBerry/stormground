namespace Test;
using SDL3;
using Storm;

public class Test : Mod {
  public override void Init (out List<SRP.RenderPass> renderPasses,
    out List<Window.Subscription> subscriptions) {
    renderPasses  = [];
    subscriptions = [];
  }

  public override void Update (double delta) {
  }
}
