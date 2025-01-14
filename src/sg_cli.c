#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sg.h"
#include "sg_version.h"
#define HYDROGEN_STRING
#define HYDROGEN_IO
#include "hydrogen.h"

#include "sgsharp.h"

static int sg_help (int argc, char** argv);
static int sg_version (int argc, char** argv);
static int sg_new (int argc, char** argv);
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
    {"new", "Create a stormground project", sg_new},
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
  printf ("Stormground version " SG_VERSION_STRING " built " SG_BUILD_DATE_NUM
          "\n");
  return 0;
}

static char const sg_default_proj[] = {
    "<sg ever=\"" SG_VERSION_STRING
    "\"><project data_ver=\"1\" main=\"main.lua\"/></sg>"};

static int sg_new (int argc, char** argv) {
  if (argc == -1) {
    printf (
        "usage: sg new <directory> <name>\n  newializes a stormground "
        "project named <name> at "
        "<directory>,\n  doing nothing if one already exists\n");
    return 0;
  }
  if (argc < 2) {
    sg_new (-1, NULL);
    return 1;
  }
  sgsharp_new (argv[0], argv[1]);
  /*char* dir = io_absolute (argv[0]);
  if (!dir) {
    fprintf (stderr, "an error occured while fixing path\n");
    return 1;
  }
  char* sgdir = str_fmt ("%s/.sg", dir);
  if (io_exists (dir)) {
    if (io_exists (sgdir)) {
      printf ("a stormground project already exists at that directory\n");
      free (sgdir);
      return 0;
    }
  }
  io_mkdir (dir);
  io_mkdir (sgdir);
  io_hide (sgdir);
  char* xmlpath = str_fmt ("%s/project.xml", sgdir);
  FILE* F       = fopen (xmlpath, "w");
  free (xmlpath);
  if (!F) {
    fprintf (stderr, "failed to create project.xml\n");
    return 1;
  }
  fwrite (sg_default_proj, 1, sizeof (sg_default_proj) - 1, F);

  printf ("created project %s at %s\n", argv[1], dir);

  fclose (F);
  free (sgdir);
  free (dir);*/
  return 0;
}

static int sg_run (int argc, char** argv) {
  if (argc == -1) {
    printf (
        "usage: sg run [<directory>]\n  Runs a stormground project at "
        "<directory>,\n  attempting to run at cwd if <directory> isnt given\n");
    return 0;
  }
  return 0;
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
