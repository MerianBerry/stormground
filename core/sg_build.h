#ifndef SG_BUILD_H
#define SG_BUILD_H

#include "sg.h"
#include "sg_lua.h"

typedef struct SG_BuildInfo {
  char const **depv;
  uint32_t     depc;
} SG_BuildInfo;

int sg_runBuild (SG *sg);

int sg_buildShaders (SG *sg, SG_BuildInfo *bi);

int sg_downloadDeps (SG *sg, SG_BuildInfo *bi);
#endif