#include "sg.h"

#include "cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int sg_help (SGstate*, int argc, char** argv);
static int sg_run (SGstate*, int argc, char** argv);
static int sg_version (SGstate*, int argc, char** argv);
static int sgGetProjectSets (SGstate* sgs);

typedef int (*CmdFunction) (SGstate*, int, char**);

typedef struct Command {
  char const* name;
  char const* desc;
  CmdFunction cf;
  char const* aliass[3];
} Command;

static const Command cmds[] = {
    {"help",    "Prints usage of stormground.",     sg_help,    {"-h", NULL}},
    {"run",     "Runs stormground in a directory.", sg_run,     {"-r", NULL}},
    {"version", "Prints version info.",             sg_version, {"-v", NULL}},
};

Command const* sg_matchcmd (char const* name) {
  int i;
  for (i = 0; i < sizeof (cmds) / sizeof (cmds[0]); i++) {
    char aliased = 0;
    int  j;
    for (j = 0; cmds[i].aliass && cmds[i].aliass[j]; j++) {
      if (!strcmp (cmds[i].aliass[j], name)) {
        aliased = 1;
        break;
      }
    }
    if (!strcmp (cmds[i].name, name) || aliased)
      return cmds + i;
  }
  return NULL;
}

static void sg_printcmd (Command const* cmd) {
  int j;
  printf ("%s", cmd->name);
  if (cmd->aliass) {
    printf (" [");
    for (j = 0; cmd->aliass[j]; j++)
      printf ("%s,", cmd->aliass[j]);
    printf ("\b]");
  }
  printf (": %s\n", cmd->desc);
}

static int sg_help (SGstate* sgs, int argc, char** argv) {
  sgs->runstate = SG_RUNSTATE_STOP;
  if (argc < 1) {
    int i;
    printf ("Usage: sg <command> [<args>]\n\n");
    printf ("Commands:\n");
    for (i = 0; i < sizeof (cmds) / sizeof (cmds[0]); i++) {
      int j;
      printf ("   ");
      sg_printcmd (&cmds[i]);
    }
    printf ("\nFor details about a command, use:\n   sg help <command>\n");
    return 0;
  }
  Command const* cmd = sg_matchcmd (argv[0]);
  if (!cmd) {
    printf ("Unknown command \"%s\".\n", argv[0]);
    return sg_help (sgs, 0, NULL);
  }
  return cmd->cf (sgs, -1, NULL);
}

static int sg_run (SGstate* sgs, int argc, char** argv) {
  int r;
  if (argc < 0) {
    sg_printcmd (sg_matchcmd ("run"));
    printf (
        "usage:\n   sg run [<dir>]\n   Runs stormground in <dir>, attempting "
        "to "
        "run at cwd if <dir> isnt given.\n");
    printf (
        "\nThis command is ran if no commands are "
        "given.\n");
    return 0;
  }
  if (argc == 0) {
    sgs->projectDir = ".";
  } else
    sgs->projectDir = argv[0];
  if ((r = scl_chdir (sgs->projectDir)))
    return fprintf (stderr, "Failed to change dir to \"%s\"\n",
                    scl_realpath (sgs->projectDir)),
           r;
  if ((r = sgGetProjectSets (sgs)))
    return r;
  return 0;
}

static int sg_version (SGstate* sgs, int argc, char** argv) {
  sgs->runstate = SG_RUNSTATE_STOP;
  if (argc < 0)
    return sg_printcmd (sg_matchcmd ("version")), 0;
  printf ("Stormground v" SG_VERNAME "\n");
  return 0;
}

int sgRunCli (SGstate* sgs, int argc, char** argv) {
  if (argc < 2) {
    return sg_run (sgs, 0, NULL);
  }
  Command const* cmd = sg_matchcmd (argv[1]);
  if (!cmd) {
    fprintf (stderr, "Unrecognized command \"%s\"\n", argv[1]);
    return sg_help (NULL, 0, NULL), 1;
  }
  return cmd->cf (sgs, argc - 2, argv + 2);
}

static int sgGetProjectSets (SGstate* sgs) {
  // Project jsons are nolonger required
  if (!scl_exists ("sgproject.json"))
    return 0;
  scl_file* f = scl_open ("r", "sgproject.json");
  if (!f) {
    return fprintf (stderr, "Failed to open sgproject.json.\n"), 1;
  }
  char* content;
  scl_read_malloc (f, (void**)&content, -1);
  if (!content) {
    return fprintf (stderr, "Failed to read sgproject.json.\n"), 1;
  }
  scl_close (f);

  cJSON* projectJSON = cJSON_Parse (content);
  if (!projectJSON) {
    fprintf (stderr, "Failed to parse project json:\n\t%s\n",
             cJSON_GetErrorPtr());
    return 1;
  }
  if (projectJSON->type != cJSON_Object || !projectJSON->child)
    return fprintf (stderr, "Malformed project json.\n"), 1;
  cJSON* itr = projectJSON->child;
  while (itr) {
    if (!strcmp (itr->string, "monitorWidth") && itr->type == cJSON_Number) {
      sgs->width = itr->valueint;
      if (sgs->width > SG_MAX_MONWIDTH)
        printf (
            "Window width parameter is too high, and will be clamped (%i)\n",
            SG_MAX_MONWIDTH);
      sgs->width = clampf (sgs->width, 6, SG_MAX_MONWIDTH);
    } else if (!strcmp (itr->string, "monitorHeight") &&
               itr->type == cJSON_Number) {
      sgs->height = itr->valueint;
      if (sgs->height > SG_MAX_MONHEIGHT)
        printf (
            "Window height parameter is too high, and will be clamped (%i)\n",
            SG_MAX_MONHEIGHT);
      sgs->height = clampf (sgs->height, 6, SG_MAX_MONHEIGHT);
    } else if (!strcmp (itr->string, "name") && itr->type == cJSON_String) {
      sgs->name = (char*)scl_strcopy (itr->valuestring);
    }
    itr = itr->next;
  }
  if (!sgs->name)
    sgs->name = (char*)scl_strcopy ("Stormground " SG_VERNAME);

  cJSON_Delete (projectJSON);
  return 0;
}