#define _XOPEN_SOURCE 700
#include "sgcli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#if defined(__unix__)
#  include <unistd.h>
#elif defined(_WIN32)

#endif

typedef int (*FlagCallback) (SGstate*, int, char**);

typedef struct flag {
  char const*  flag;
  char const*  name;
  char const*  desc;
  FlagCallback fc;
} flag;

static const flag flags[] = {
    (flag){"-h", "Help",
           "Prints a list of the supported flags of this\n\t"
           "program. AKA what you are seeing now",                              sg_help},
    (flag){"-d", "Directory",
           "Run stormgound in target\n\t"
           "directoryrelative to current working directory",                    sg_dir },
    (flag){"-v", "Version",   "Prints the current Stormground program version",
           sg_ver                                                                      },
};

int sg_help (SGstate* sgs, int argc, char** argv) {
  int i;
  int s = sizeof (flags) / sizeof (flag);
  for (i = 0; i < s; ++i) {
    flag f = flags[i];
    printf ("%s (%s) %s\n", f.flag, f.name, f.desc);
  }
  return 0;
}

int sg_dir (SGstate* sgs, int argc, char** argv) {
  if (argc != 1) {
    errorf ("Directory flag requires 1 argument\n");
    return -1;
  }
  sgs->projectDir = (char*)str_cpy (argv[0], npos);
  return 1;
}

int sg_ver (SGstate* sgs, int argc, char** argv) {
  printf (
      "Stormground (sg) version v%i.%i\nA Stormworks Lua render api replica "
      "made by Merian\n",
      SG_MAJOR, SG_MINOR);
  return 0;
}

char** getNextArgs (int i, int* vc, int argc, char** argv) {
  char** v = NULL;
  int    c = 0;
  for (i = i + 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      v = mem_grow (v, sizeof (char*), c, &argv[i], 1);
      ++c;
    }
  }
  (*vc) = c;
  return v;
}

int doTheDoThing (SGstate* sgs, int argc, char** argv) {
  int i;
  int i2;
  int flagc = sizeof (flags) / sizeof (flag);
  for (i = 1; i < argc; ++i) {
    for (i2 = 0; i2 < flagc; ++i2) {
      flag f = flags[i2];
      if (!strcmp (f.flag, argv[i])) {
        int    c = 0;
        char** v = getNextArgs (i, &c, argc, argv);
        int    r = f.fc (sgs, c, v);
        free (v);
        if (r < 0)
          return 1;
        i += r;
        break;
      }
    }
  }
  char* realreal = io_fullpath (sgs->projectDir);
  free ((void*)sgs->projectDir);
  sgs->projectDir = realreal;

  if (io_changedir (sgs->projectDir)) {
    errorf ("Failed to change directory\n");
    return 1;
  }

  h_buffer projectContent = io_read ("project.json");
  if (!projectContent.data) {
    errorf ("Could not open project.json in (%s)\n", sgs->projectDir);
    return 1;
  }
  sgs->projectFileContent = projectContent;

  FILE* pmain = fopen ("main.lua", "r");
  if (!pmain) {
    errorf ("Could not open main.lua in (%s)\n", sgs->projectDir);
    return 1;
  }
  fclose (pmain);

  return 0;
}