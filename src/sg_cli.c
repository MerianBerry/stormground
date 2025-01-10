#include <stdio.h>
#include <string.h>

#include "sg.h"
#include "sg_version.h"

static int sg_help (int argc, char** argv);
static int sg_version (int argc, char** argv);
static int sg_init (int argc, char** argv);
static int sg_run (int argc, char** argv);
static int sg_debug (int argc, char** argv);

typedef int (*sg_cmdfun) (int, char**);

struct sg_command {
  char const* name;
  char const* desc;
  sg_cmdfun   cb;
};

static const struct sg_command cmds[] = {
    {"help", "Describe usage of commands", sg_help},
    {"version", "Output this stormground's version", sg_version},
    {"init", "Create a stormground project", sg_init},
    {"run", "Run a stormground project", sg_run},
    {"debug", "Debug a stormground project", sg_debug},
};

static int sg_help (int argc, char** argv) {
  printf ("usage: sg <command> [<args>]\n\n");
  printf ("Heres a list of commands:\n\n");
  for (size_t i = 0; i < sizeof (cmds) / sizeof (struct sg_command); i++) {
    printf ("  %s", cmds[i].name);
    for (int j = 0; j < 10 - strlen (cmds[i].name); j++) {
      printf (" ");
    }
    printf ("%s\n", cmds[i].desc);
  }
  printf (
      "\nFor details about a command, use:\n  sg help "
      "<command>\n");
  return 0;
}

static int sg_version (int argc, char** argv) {
  printf ("Stormground " SG_VERSION_STRING "\n  Built on " SG_BUILD_DATE "\n");
  return 0;
}

static int sg_init (int argc, char** argv) {
  return 0;
}

static int sg_run (int argc, char** argv) {
  return 0;
}

static int sg_debug (int argc, char** argv) {
  return 0;
}

int sg_handleArgs (int argc, char** argv) {
  sg_help (argc, argv);
  sg_version (argc, argv);
  return 0;
}
