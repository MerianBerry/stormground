#include <stdio.h>

#include "sg.h"
#include "sg_version.h"
#include "SDL3/SDL.h"

#include "macl.h"


extern char const mobdebug_lua[];
extern char const socket_lua[];

#ifdef SG_INCLUDE_GENERATED
#  include "mobdebug.h"
#  include "socket.h"
#else
#endif

int main (int argc, char** argv) {
  // int                  r         = sg_handleArgs (argc, argv);
  return 0;
  /*MonoDomain* domain;
  domain = mono_jit_init ("Stormground");*/

  /*int r = sg_handleArgs (argc, argv);

  if (!SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    fprintf (stderr, "failed to start sdl\n");
    return 1;
  }
  SDL_Window* win = SDL_CreateWindow ("Stormground", 500, 500, 0);
  int         run = 1;
  while (run) {
    SDL_Event e;
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        run = 0;
        break;
      }
    }
    t_waitms (16.6);
  }
  SDL_DestroyWindow (win);
  SDL_Quit();
  return r;*/
}
