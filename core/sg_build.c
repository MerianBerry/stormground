#include "sg_build.h"
#include "scl.h"
#include <stdio.h>
#include "SDL3/SDL_thread.h"
#include "libgit2/include/git2/clone.h"
#include "libgit2/include/git2.h"

typedef struct ThreadedState {
  SDL_Thread *workerv[SG_WORKER_SIZE];
  int         wstatev[SG_WORKER_SIZE];
  SDL_Mutex  *m;
} ThreadedState;

typedef struct WorkerParam {
  ThreadedState *ts;
  SG_BuildInfo  *bi;
  int            indx;
} WorkerParam;

static int gitWorker (WorkerParam *p) {
  git_libgit2_init();
  git_libgit2_shutdown();
}

int sg_downloadDeps (SG *sg, SG_BuildInfo *bi) {
  ThreadedState ts;
  memset (&ts, 0, sizeof (ts));
  ts.m = SDL_CreateMutex();

  WorkerParam wp = {
    .ts   = NULL,
    .bi   = bi,
    .indx = 0,
  };

  // SDL_Thread *t = SDL_CreateThread ((SDL_ThreadFunction)gitWorker, "H", &wp);

  char const *progress = "/-\\|";
  int         p        = 0;

  return 0;
}
