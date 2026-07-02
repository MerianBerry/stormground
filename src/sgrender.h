#ifndef SG_RENDER_H
#define SG_RENDER_H
#include "sg.h"

int sgInitRenderPipe();

int sgDrawRenderPipe();

int sgRenderOpenLibs (lua_State* L);
#endif