#ifndef SG_H
#  include "sgconf.h"
#  include "SDL3/SDL.h"

typedef struct SG {
  SDL_Window*    win;
  SDL_GPUDevice* dev;
} SG;

extern SG sg_;

int sg_mainInit (SG*);

int sg_handleArgs (int argc, char** argv);
#endif