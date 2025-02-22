namespace Storm;

public abstract class Mod {
  public abstract void Init(out List<Window.Subscription> subscriptions);
}