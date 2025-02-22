namespace Storm.Core;
using System.Reflection;
using System.Runtime;

public static class Main {
  public static IntPtr sglu = 0;
  public static List<GPU.Backend> backendPriority = [GPU.Backend.Direct3D12, GPU.Backend.Metal, GPU.Backend.Vulkan];
  public static Window? rootWindow;
  public static Mod? rootMod;
  public static string ExecuteDir;
  
  public static void EntryFromCore(string edir, string usrdll) {
    ExecuteDir = edir;
    var asm = Assembly.LoadFile(usrdll) ??
      throw new Exception("Coudln't load user assembly");
    var modtype = typeof(Mod);
    var types = asm.GetTypes().Where(p => modtype.IsAssignableFrom(p));
    if (!types.Any()) {
      Console.WriteLine("Couldn't find any valid mod classes");
      return;
    }

    rootMod = Activator.CreateInstance(types.First()) as Mod;
    List<Window.Subscription> subscriptions = [];
    rootMod.Init(out subscriptions);
    rootWindow = new("Stormground 2", SDL3.SDL.SDL_WindowFlags.SDL_WINDOW_RESIZABLE);
    foreach (var sub in subscriptions) {
      rootWindow.Subscribe(sub);
    }

    if (rootWindow == null)
      return;
    try {
      while (rootWindow) {
        Update();
      }
    } catch(Exception e) {
      Console.WriteLine(e.Message);
    }
  }

  public static void Update() {
    rootWindow.Update();
  }
}
