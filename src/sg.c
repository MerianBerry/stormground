#include <stdio.h>

#include "sg.h"
#include "sg_version.h"
#include "SDL3/SDL.h"

#include "scl.h"
#define HYDROGEN_TIME
#include "hydrogen.h"


extern char const mobdebug_lua[];
extern char const socket_lua[];

#ifdef SG_INCLUDE_GENERATED
#  include "mobdebug.h"
#  include "socket.h"
#else
#endif

int main (int argc, char **argv) {
// int                  r         = sg_handleArgs (argc, argv);
#if 1
  xml_doc *doc = xml_parse_string (
    "<veh><hell hi=\"2\"><yo j=\"24\"/><yo j=\"25\"/></hell></veh>");
  xml_node **xpaths = xml_xpath (doc->root, "/hell/yo[1]");
#else
  ion_file *f = ion_open ("r", "piss.xml");
  char     *str;
  ion_read_malloc (f, (void **)&str, -1);
  size_t      size = strlen (str);
  h_timepoint ts   = timenow();
  xml_doc    *doc  = xml_parse_string (str);
  h_timepoint te   = timenow();
  char const *ostr = xml_print (doc);
  h_timepoint te2  = timenow();
  free ((void *)str);
  xml_free_doc (doc);
  double mb = (double)size / 1000000.0;
  double t1 = timeduration (te, ts, seconds_e);
  double t2 = timeduration (te2, te, seconds_e);
  printf ("file: %0.2lfMB\n", (double)size / 1000000.0);
  printf (
    "parsing took %0.3lf seconds (%0.3lfMB/s)\nprinting took %0.2lf seconds "
    "(%0.2lfMB/s)\n",
    t1,
    mb / t1,
    t2,
    mb / t2);
  if (ostr) {
    ion_file *f2 = ion_open ("w", "piss2.xml");
    ion_write_str (f2, ostr);
    free ((void *)ostr);
    ion_close (f2);
  }
  ion_close (f);
#endif
  return 0;
  /*MonoDomain* domain;
  domain = mono_jit_init ("Stormground");*/

  /*int r = sg_handleArgs (argc, argv);

  if (!SDL_Init (SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    fprintf (stderr, "failed to start sdl\n");
    return 1;
  }
  SDL_Window* win = SDL_CreateWindow ("Stormground", 500, 500, 0);
  int         run = 1;
  while (run) {
    SDL_Event e;
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        run = 0;
        break;
      }
    }
    t_waitms (16.6);
  }
  SDL_DestroyWindow (win);
  SDL_Quit();
  return r;*/
}
