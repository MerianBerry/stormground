#include "SDL3/SDL.h"
#include "sg.h"
#include "sg_lua.h"
#include "sg_event.h"
#include "sg_render.h"
#include "sg_build.h"
#include <stdio.h>
#include <fcntl.h>

#ifdef _WIN32
#  include <io.h>
#endif

SG sg_;

static int sg_mainLoop (SG* sg);

EXPORT char const* WHAT =
  "sg#############################################################";

int main (int argc, char** argv) {
#ifdef _WIN32
  _dup2 (_fileno (stdout), _fileno (stderr));
#endif

  return sg_handleArgs (argc, argv);
}

#ifdef _WIN32
static void get_command_line_args (int* argc, char*** argv) {
  LPWSTR* wargv = CommandLineToArgvW (GetCommandLineW(), argc);
  if (!wargv) {
    *argc = 0;
    *argv = NULL;
    return;
  }

  int n = 0;
  for (int i = 0; i < *argc; i++)
    n +=
      WideCharToMultiByte (CP_UTF8, 0, wargv[i], -1, NULL, 0, NULL, NULL) + 1;

  *argv = malloc ((*argc + 1) * sizeof (char*) + n);
  if (!*argv) {
    *argc = 0;
    return;
  }

  char* arg = (char*)&((*argv)[*argc + 1]);
  for (int i = 0; i < *argc; i++) {
    (*argv)[i] = arg;
    arg +=
      WideCharToMultiByte (CP_UTF8, 0, wargv[i], -1, arg, n, NULL, NULL) + 1;
  }
  (*argv)[*argc] = NULL;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nShowCmd) {
  int    argc = 0;
  char** argv = NULL;
  get_command_line_args (&argc, &argv);
  // sg_createConsole();

  return main (argc, argv);
}
#endif

int sg_mainInit (SG* sg, char const* dir) {
  memset (sg, 0, sizeof (SG));
  sg->runstate = 1;
  sg->wdir     = dir;

  sg_loadMappings (sg);

  sg_runBuild (sg);

  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

  sg->win = SDL_CreateWindow ("Stormground " SG_VERSION_STRING,
    500,
    500,
    SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
  SDL_GetWindowSize (sg->win, (int*)&sg->lw, (int*)&sg->lh);
  sg->dev = SDL_CreateGPUDevice (SG_SHADERFORMAT, 0, NULL);
  if (!SDL_ClaimWindowForGPUDevice (sg->dev, sg->win)) {
    sg_logErrorf ("failed to claim gpu for window: %s", SDL_GetError());
    return 1;
  }
  SDL_ShowWindow (sg->win);


  sg_luaInit (sg);
  sg_runInit (sg, dir);
  fflush (stdout);

  // SDL_GPU_SHADERFORMAT_DXBC

  sg_mainLoop (sg);
  return 0;
}

static int sg_mainLoop (SG* sg) {
  while (sg->runstate) {
    SDL_Event e;
    while (SDL_PollEvent (&e)) {
      sg_processEvent (sg, &e);
    }
    sg_runTicks (sg);
    fflush (stdout);
    sg_renderFrame (sg);
    sg_advanceInputs (sg);
  }
end_loop:
  return 0;
}
