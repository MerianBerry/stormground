namespace SG.Core;

using System.Runtime.InteropServices;
using SG;

using SDL3;

public static class Main {
  
  public static IntPtr sglu = 0;
  public static IntPtr Fuck = 0;
  public static void EntryFromCore(string str) {
    SDL.SDL_Init(SDL.SDL_InitFlags.SDL_INIT_VIDEO);
    IntPtr win = SDL.SDL_CreateWindow("Hallo", 500, 500, 0);
    bool run = true;
    while (run) {
      SDL.SDL_Event e;
      while (SDL.SDL_PollEvent(out e)) {
        if (e.type == (uint)SDL.SDL_EventType.SDL_EVENT_QUIT) {
          run = false;
          break;
        }
      }
      Thread.Sleep(17);
    }
    SDL.SDL_DestroyWindow(win);
    SDL.SDL_Quit();
  }
}
