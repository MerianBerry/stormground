namespace Storm.Core;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices.Marshalling;
using System.Threading.Tasks;

public static class Main {
  public static IntPtr            sglu = 0;
  public static List<SRP.Backend> backendPriority =
    [SRP.Backend.Direct3D12, SRP.Backend.Metal, SRP.Backend.Vulkan];
  public static Window? rootWindow;
  public static Mod? rootMod;
  public static string  ExecuteDir = "";
  private static double delta      = 0.0;

  public static void EntryFromCore ([MarshalUsing (
    typeof (Native.CallerOwnedStringMarshaller))] string usrdll) {
    if (usrdll == "") {
      throw new NotImplementedException (
        "Usrdll post launch search functionality not implemented");
    }
    try {
      string dir = AppDomain.CurrentDomain.BaseDirectory;
      // ExecuteDir = edir;
      var asm = Assembly.LoadFile (usrdll) ??
                throw new Exception ("Coudln't load user assembly");
      var modtype = typeof (Mod);
      var types   = asm.GetTypes().Where (p => modtype.IsAssignableFrom (p));
      if (!types.Any())
        throw new Exception ("Couldn't find any valid Mod classes");

      rootWindow =
        new("Stormground 2", SDL3.SDL.SDL_WindowFlags.SDL_WINDOW_RESIZABLE);

      ShaderWorker worker = new();
      Task.Run (() => worker.Start (rootWindow.SRP));


      rootMod = Activator.CreateInstance (types.First()) as Mod;
      List<SRP.RenderPass>      renderPasses  = [];
      List<Window.Subscription> subscriptions = [];
      rootMod.Init (out renderPasses, out subscriptions);
      foreach (var sub in subscriptions) {
        rootWindow.Subscribe (sub);
      }
    } catch (Exception e) {
      Native.Storm_LogError ("Storm", e.Message, e.StackTrace);
      return;
    }

    rootWindow.Show();

    if (rootWindow == null)
      return;
    try {
      while (Update()) {
      }
    } catch (Exception e) {
      Native.Storm_LogError ("Storm", e.Message, e.StackTrace);
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

  public static void BuildFromCore (string dir) {
    string str = "\"ss\"";
  }
}
