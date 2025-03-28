#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sg.h"
#include "scl.h"
#include "sg_version.h"

static int sg_help (int argc, char** argv);
static int sg_version (int argc, char** argv);
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
  {"version", "Displays stormground's version info", sg_version},
  {"run", "Run a stormground project", sg_run},
  {"debug", "Debug a stormground project", sg_debug},
};

static sg_cmdfun sg_matchcmd (char const* arg) {
  if (!arg)
    return NULL;
  for (int i = 0; i < sizeof (cmds) / sizeof (struct sg_command); i++) {
    if (!strcmp (cmds[i].name, arg)) {
      return cmds[i].cb;
    }
  }
  return NULL;
}

static int sg_help (int argc, char** argv) {
  if (argc == -1) {
    printf (
      "usage: sg help [<command>]\n  Prints stormground cli information or "
      "information about the given command\n");
    return 0;
  }
  if (argc > 0) {
    sg_cmdfun cb = sg_matchcmd (argv[0]);
    if (!cb) {
      sg_help (0, NULL);
      return 1;
    }
    cb (-1, NULL);
    return 0;
  }
  printf ("usage: sg <command> [<args>]\n\n");
  printf ("Heres a list of commands:\n\n");
  for (int i = 0; i < sizeof (cmds) / sizeof (struct sg_command); i++) {
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
  if (argc == -1) {
    printf (
      "usage: sg version\n  Displays stormground's version "
      "info\n");
    return 0;
  }
  printf (
    "Stormground version " SG_VERSION_STRING " built " SG_BUILD_DATE_NUM "\n");
  return 0;
}

static char const sg_default_proj[] = {
  "<sg ever=\"" SG_VERSION_STRING
  "\"><project data_ver=\"1\" main=\"main.lua\"/></sg>"};

static int sg_run (int argc, char** argv) {
  if (argc == -1) {
    printf (
      "usage: sg run [<directory>]\n  Runs a stormground project at "
      "<directory>,\n  attempting to run at cwd if <directory> isnt given\n");
    return 0;
  }
  char const* dir = *argv ? *argv : ".";
  return sg_mainInit (&sg_, dir);
}

static int sg_debug (int argc, char** argv) {
  if (argc == -1) {
    printf (
      "usage: sg debug [<directory>]\n  Starts a debug session on a "
      "stormground project at "
      "<directory>,\n  attempting to run at cwd if <directory> isnt given\n");
    return 0;
  }
  return 0;
}

int sg_handleArgs (int argc, char** argv) {
  if (argc <= 1 && !argv) {
    sg_help (0, NULL);
    return 1;
  }
  argc--;
  argv++;
  sg_cmdfun cb = sg_matchcmd (argv[0]);
  if (!cb) {
    sg_help (0, NULL);
    return 1;
  }
  return cb (argc - 1, argv + 1);
}
