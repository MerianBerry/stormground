#include "sg.h"

#include "cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int sg_help (SGstate*, int argc, char** argv);
static int sg_run (SGstate*, int argc, char** argv);

typedef int (*CmdFunction) (SGstate*, int, char**);

typedef struct Command {
  char const* name;
  char const* alias;
  char const* desc;
  CmdFunction cf;
} Command;

static const Command cmds[] = {
    {"help", NULL,
     "Prints usage of commands.\nUse sg help <command> for detailed "
     "information about a command.", sg_help},
    {"-h",   "help", NULL,           NULL   },
};

Command const* sg_matchcmd (char const* name) {
  int i;
  for (i = 0; i < sizeof (cmds) / sizeof (cmds[0]); i++) {
    if (!strcmp (cmds[i].name, name) ||
        (cmds[i].alias && !strcmp (cmds[i].alias, name))) {
      return cmds + i;
    }
  }
  return NULL;
}

static int sg_help (SGstate* sgs, int argc, char** argv) {
  if (argc < 1) {
  }
}

static int sg_run (SGstate* sgs, int argc, char** argv) {
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

int sgGetProjectSets (SGstate* sgs) {
  scl_file* f = scl_open ("r", "sgproject.json");
  if (!f) {
  }
  char* content;
  scl_read_malloc (f, (void**)&content, -1);
  if (!content) {
  }

  cJSON* projectJSON = cJSON_Parse (content);
  if (!projectJSON) {
    fprintf (stderr, "Failed to parse project json!\n\t%s\n",
             cJSON_GetErrorPtr());
    return 1;
  }
  if (projectJSON->type != cJSON_Object) {
    fprintf (stderr, "project json root is not an object\n");
    exit (2);
  }
  if (!projectJSON->child) {
    fprintf (stderr, "project json root does not have a child node\n");
    exit (2);
  }
  cJSON* itr = projectJSON->child;
  while (itr) {
    if (!strcmp (itr->string, "monitorWidth") && itr->type == cJSON_Number) {
      sgs->width = itr->valueint;
      if (sgs->width < 1 || sgs->width > 1080) {
        fprintf (
            stderr,
            "project monitor width is outside acceptable bounds\n\t%i is not "
            "within such bounds\n",
            sgs->width);
        exit (2);
      }
    } else if (!strcmp (itr->string, "monitorHeight") &&
               itr->type == cJSON_Number) {
      sgs->height = itr->valueint;
      if (sgs->height < 1 || sgs->height > 1080) {
        fprintf (
            stderr,
            "project monitor height is outside acceptable bounds\n\t%i is not "
            "within such bounds\n",
            sgs->height);
        exit (2);
      }
    } else if (!strcmp (itr->string, "name") && itr->type == cJSON_String) {
      sgs->name = (char*)scl_strcopy (itr->valuestring);
    }
    itr = itr->next;
  }
  if (!sgs->width || !sgs->height) {
    fprintf (stderr,
             "Project settings doesnt set monitor width and height. Using "
             "default: 96x96.\n");
    sgs->width  = 96;
    sgs->height = 96;
  }
  if (!sgs->name) {
    sgs->name = (char*)scl_strcopy ("stormground");
  }

  cJSON_Delete (projectJSON);
}