namespace Test;
using SDL3;
using Storm;
using Storm.Core;

public class Test : Mod {
  private class TestSub : Window.Subscription {
    public override void Event(in SDL.SDL_Event e) {
      base.Event(e);
    }
    public override void Update() {
      
    }
  }

  public override void Init(out List<Window.Subscription> subscriptions) {
    subscriptions = [];
    subscriptions.Add(new TestSub());
  }
}
