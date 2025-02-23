namespace Storm.Core;
using System.Reflection;
using System.Diagnostics;
using System.Runtime;

public static class Main {
  public static IntPtr            sglu = 0;
  public static List<SRP.Backend> backendPriority =
    [SRP.Backend.Direct3D12, SRP.Backend.Metal, SRP.Backend.Vulkan];
  public static Window? rootWindow;
  public static Mod? rootMod;
  public static string  ExecuteDir = "";
  private static double delta      = 0.0;

  public static void EntryFromCore (string edir, string usrdll) {
    if (usrdll == "") {
      throw new NotImplementedException (
        "Usrdll post launch search functionality not implemented");
    }
    try {
      ExecuteDir = edir;
      var asm    = Assembly.LoadFile (usrdll) ??
                throw new Exception ("Coudln't load user assembly");
      var modtype = typeof (Mod);
      var types   = asm.GetTypes().Where (p => modtype.IsAssignableFrom (p));
      if (!types.Any()) {
        Console.WriteLine ("Couldn't find any valid mod classes");
        return;
      }

      rootMod = Activator.CreateInstance (types.First()) as Mod;
      List<SRP.RenderPass>      renderPasses  = [];
      List<Window.Subscription> subscriptions = [];
      rootMod.Init (out renderPasses, out subscriptions);
      rootWindow =
        new("Stormground 2", SDL3.SDL.SDL_WindowFlags.SDL_WINDOW_RESIZABLE);
      foreach (var sub in subscriptions) {
        rootWindow.Subscribe (sub);
      }
    } catch (Exception e) {
      Console.WriteLine ("An error occured while initializing");
      Console.WriteLine (e.Message);
      Console.WriteLine (e.StackTrace);
      return;
    }


    if (rootWindow == null)
      return;
    try {
      while (Update()) {
      }
    } catch (Exception e) {
      Console.WriteLine ("An error occured while updating root window");
      Console.WriteLine (e.Message);
      Console.WriteLine (e.StackTrace);
    }

    rootMod.Cleanup();
  }

  public static bool Update() {
    Stopwatch watch = Stopwatch.StartNew();
    rootMod.Update (delta);
    rootWindow.Update();
    watch.Stop();
    delta = watch.Elapsed.TotalMilliseconds;
    return rootWindow;
  }
}
