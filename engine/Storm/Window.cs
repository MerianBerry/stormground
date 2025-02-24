namespace Storm;
using SDL3;

public class Window {
  public class Subscription {
    public enum SubscriptionMode {
      AfterEvents = 0,
      AtStart     = 1,
    }

    public Window? target;

    public void IntInit (in Window target) {
      this.target = target;
    }

    public virtual void Init (out SubscriptionMode mode) {
      mode = SubscriptionMode.AfterEvents;
    }

    public virtual void Event (in SDL.SDL_Event e) {
      if (e.type == (uint)SDL.SDL_EventType.SDL_EVENT_QUIT) {
        target?.Quit();
      }
    }

    public virtual void Update() {
    }
  }

  private IntPtr             handle;
  private SRP                srp;
  private List<Subscription> l1subs;
  private List<Subscription> l2subs;

  public IntPtr Handle { get => handle; }
  public SRP    SRP { get => srp; }

  private bool  run = true;
  public string title {
    get => SDL.SDL_GetWindowTitle (handle);
    set => SDL.SDL_SetWindowTitle (handle, value);
  }

  public Window (string title, SDL.SDL_WindowFlags flags = 0) {
    l1subs = [];
    l2subs = [];
    flags |= SDL.SDL_WindowFlags.SDL_WINDOW_MAXIMIZED |
             SDL.SDL_WindowFlags.SDL_WINDOW_HIDDEN;
    handle = SDL.SDL_CreateWindow (title, 1920, 1080, flags);
    srp    = new(this);
    Core.Native.Storm_LogInfo ("Engine",
      "Created new window: [title: " + title + "]",
      null);
  }

  public Window (string title, int w, int h, SDL.SDL_WindowFlags flags = 0) {
    l1subs = [];
    l2subs = [];
    handle = SDL.SDL_CreateWindow (title, w, h, flags);
    srp    = new(this);
    Core.Native.Storm_LogInfo ("Engine",
      "Created new window: [title: " + title + "]",
      null);
  }

  public void Quit() => run = false;

  public void Subscribe (Subscription sub) {
    sub.IntInit (this);
    Subscription.SubscriptionMode mode;
    sub.Init (out mode);
    if (mode == Subscription.SubscriptionMode.AtStart) {
      l1subs.Add (sub);
    } else {
      l2subs.Add (sub);
    }
  }

  public void Subscribe<T>()
    where     T : Subscription, new() {
    Type type = typeof (T);
    T    sub  = new();
    Subscribe (sub);
  }

  public void Update() {
    foreach (Subscription sub in l1subs) {
      sub.Update();
    }
    SDL.SDL_Event e;
    while (run && SDL.SDL_PollEvent (out e)) {
      foreach (var sub in l2subs) {
        sub.Event (e);
      }
    }
    if (!run) {
      srp.Destroy();
      SDL.SDL_DestroyWindow (handle);
      handle = 0;
      l2subs.Clear();
    }
    for (int i = l2subs.Count - 1; i >= 0; i--) {
      l2subs[i].Update();
    }
  }

  public void Show() => SDL.SDL_ShowWindow (handle);

  public void GetSize (out int w, out int h) => SDL.SDL_GetWindowSize (handle,
    out w, out h);

  public static implicit operator bool (Window w) => w.run;

  ~Window() {
    if (handle != 0) {
      SDL.SDL_DestroyWindow (handle);
      handle = 0;
      l1subs.Clear();
      l2subs.Clear();
    }
  }
}