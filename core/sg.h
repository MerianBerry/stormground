#ifndef SG_H
#define SG_H
#include "sgconf.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_gpu.h"
#include "luajit/src/lua.h"
#include "luajit/src/lualib.h"
#include "luajit/src/lauxlib.h"

#define SDL_LAST_KEY SDLK_ENDCALL - SDLK_CAPSLOCK + SDLK_PLUSMINUS + 1

typedef struct SG_RT SG_RT;

typedef struct SG {
  char           keys[SDL_LAST_KEY + 1];
  char           buttons[8];
  SDL_GPUFence*  fences[SG_MAX_FENCES];
  SDL_Window*    win;
  SDL_GPUDevice* dev;
  char const*    wdir;
  lua_State*     L;
  SG_RT*         swap;
  SG_RT*         depth;
  uint32_t       lw, lh;
  int            fencec;
  int            runstate;
  int            cx, cy, cw;
} SG;

extern SG sg_;

int sg_mainInit (SG*, char const* dir);

int sg_handleArgs (int argc, char** argv);

void sg_createConsole();

#endif