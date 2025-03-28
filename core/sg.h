#ifndef SG_H
#define SG_H
#include "sgconf.h"
#include "SDL3/SDL.h"
#include "luajit/src/luaconf.h"
#include "luajit/src/lua.h"

typedef struct SG {
  SDL_Window*    win;
  SDL_GPUDevice* dev;
  char const*    wdir;
  lua_State*     L;
} SG;

extern SG sg_;

int sg_mainInit (SG*, char const* dir);

int sg_handleArgs (int argc, char** argv);


#endif