#include "SDL3/SDL.h"
#include "sg.h"
#include "sg_lua.h"
#include "sg_build.h"
#include "sg_log.h"
#include "scl.h"
#include <stdio.h>

SG sg_;

static int sg_mainLoop (SG* sg);

EXPORT char const* WHAT =
  "sg#############################################################";

int main (int argc, char** argv) {
  return sg_handleArgs (argc, argv);
}

int sg_mainInit (SG* sg, char const* dir) {
  memset (sg, 0, sizeof (SG));
  sg->wdir = dir;

  SG_BuildInfo bi;
  sg_runBuild (sg, &bi);
  sg_downloadDeps (sg, &bi);

  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

  sg->win = SDL_CreateWindow ("Stormground " SG_VERSION_STRING,
    500,
    500,
    SDL_WINDOW_HIDDEN);
  sg->dev = SDL_CreateGPUDevice (SG_SHADERFORMAT, 0, NULL);
  SDL_ClaimWindowForGPUDevice (sg->dev, sg->win);
  SDL_ShowWindow (sg->win);

  /*if (!scl_existsf ("%s/main.lua", dir)) {
    sg_echo (1);
    sg_logError ("sg", "main.lua does not exist in working directory\n");
    sg_echo (0);
    return 1;
  }*/


  sg_luaInit (sg);

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
    }
    scl_waitms (16.67);
  }
end_loop:
  return 0;
}
