#include "sg_build.h"
#include "scl.h"
#include <stdio.h>
#include "SDL3/SDL_thread.h"
#include "libgit2/include/git2/clone.h"
#include "libgit2/include/git2.h"

static void checkSGDir (char const *dir) {
  char const *sgdir = scl_fmt ("%s/.sg", dir);
  if (!scl_exists (sgdir)) {
    scl_mkdir (sgdir);
  }
}

static int configBuild (SG *sg, SG_BuildInfo *bi, char const *wdir) {
  lua_State  *L      = sg->L;
  char const *script = scl_fmt ("%s/build.lua", wdir);

  if (!scl_exists (script)) {
    sg_echoError ("%s does not exist");
    free ((void *)script);
    return 1;
  }

  luaL_dofile (L, script);

  if (!lua_testtype (L, -1, LUA_TTABLE)) {
    sg_echoErrorf ("%s did not return a table", script);
    free ((void *)script);
    return 1;
  }
  free ((void *)script);

  lua_getfield (L, -1, "plugins");

  if (lua_testtype (L, -1, LUA_TTABLE)) {
    int n = lua_objlen (L, -1);
    for (int i = 1; i <= n; i++) {
      // plugins table element
      lua_rawgeti (L, -1, i);
      // element is a simple plugin string
      if (lua_testtype (L, -1, LUA_TSTRING)) {
        char const *s        = lua_tostring (L, -1);
        bi->depv[bi->depc++] = scl_strcopy (s);
        sg_logInfof ("sg", "found plugin %s", s);
      }
      // pop the plugin table element
      lua_pop (L, 1);
    }
  }
  lua_pop (L, 1);

  lua_getfield (L, -1, "build");
  if (lua_testtype (L, -1, LUA_TFUNCTION)) {
    lua_pcall (L, 0, 0, 0);
    fflush (stdout);
  }
  lua_pop (L, 1);

  return 0;
}

int sg_runBuild (SG *sg) {
  SG_BuildInfo bi;
  memset (&bi, 0, sizeof (bi));
  bi.depv = malloc (sizeof (char *) * SG_MAX_DEPS);
  memset (bi.depv, 0, sizeof (char *) * SG_MAX_DEPS);

  checkSGDir (sg->wdir);
  sg_luaInit (sg);

  /*xml_doc  *doc  = xml_new_doc();
  xml_elem *root = xml_new_elem (doc, "words", NULL);
  xml_add_root (doc, root);

  scl_htab *h = scl_htabnew();
  scl_htabset (h, "SG", "hallo");
  scl_htabset (h, "a", "SDLK_A");
  void *ptr = scl_htabget (h, "SG");

  char const *k = NULL;
  while ((k = scl_htabnext (h, k))) {
    void     *ptr = scl_htabget (h, k);
    xml_elem *e   = xml_new_elem (doc, "t", NULL);
    xml_add_attr (e, xml_str_attribute (k, ptr));
    // xml_add_attr (e, xml_str_attribute ("out", ptr));
    xml_add_child (root, e);
    sg_logInfof ("sg", "%s: %p", k, ptr);
  }
  char const *xdoc = xml_print (doc);
  char const *xout = scl_fmt ("%s/.sg/manifest.xml", sg->wdir);
  scl_file   *f    = scl_open ("w", xout);
  free ((void *)xout);
  if (f && xdoc) {
    scl_write_str (f, xdoc);
    free ((void *)xdoc);
    scl_close (f);
  }*/

  xml_xpath ("//t[@*]");

  if (configBuild (sg, &bi, sg->wdir))
    return 1;

  lua_close (sg->L);
  return 0;
}

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
