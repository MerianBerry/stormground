#ifndef SG_EVENT_H
#define SG_EVENT_H

#include "sg.h"

#define SG_KEY_NONE     0
#define SG_KEY_PRESSED  1
#define SG_KEY_RELEASED 2
#define SG_KEY_HELD     3

int sg_loadEventLib (lua_State *L);

void sg_loadMappings (SG *sg);

int sg_processEvent (SG *sg, SDL_Event *e);

void sg_advanceInputs (SG *sg);
#endif