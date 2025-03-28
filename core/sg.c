#include "SDL3/SDL.h"
#include "sg.h"
#include "scl.h"
#include <stdio.h>

SG sg_;

static int sg_mainLoop (SG* sg);

EXPORT char const* WHAT =
  "sg#############################################################";

int main (int argc, char** argv) {
  return sg_handleArgs (argc, argv);
}

int sg_mainInit (SG* sg) {
  memset (sg, 0, sizeof (SG));
  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

  sg->win = SDL_CreateWindow ("Stormground " SG_VERSION_STRING,
    500,
    500,
    SDL_WINDOW_HIDDEN);
  sg->dev = SDL_CreateGPUDevice (SG_SHADERFORMAT, 0, NULL);
  SDL_ClaimWindowForGPUDevice (sg->dev, sg->win);
  SDL_ShowWindow (sg->win);


  sg_mainLoop (sg);
  return 0;
}

static int sg_mainLoop (SG* sg) {
  int run = 1;
  while (run) {
    SDL_Event e;
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        goto end_loop;
      }
      scl_waitms (16.67);
    }
  }
end_loop:
  return 0;
}
