namespace Storm;

/// <summary>
/// An Interface Class for user code to be ran by stormground.
/// </summary>
public abstract class Mod {
  /// <summary>
  /// Called by stormground when it is initializing a mod
  /// </summary>
  /// <param name="passes">A list of render passes to be added to the root
  /// window SRP</param> <param name="subscriptions">A list of subscriptions to
  /// be added to the root window</param>
  public abstract void Init (out List<SRP.RenderPass> passes,
    out List<Window.Subscription> subscriptions);

  public abstract void Update (double delta);

  public virtual void Cleanup() {
  }
}