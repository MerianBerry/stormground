#include "sgsharp.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <ctype.h>
#include <string.h>

#define HYDROGEN_STRING
#define HYDROGEN_IO
#include "hydrogen.h"

#ifndef __FUNCTION_NAME__
#  ifdef _WIN32 // WINDOWS
#    define __FUNCTION_NAME__ __FUNCTION__
#  else //*NIX
#    define __FUNCTION_NAME__ __func__
#  endif
#endif

void sgsharp_catch (char const* msg) {}

int sgsharp_new (char const* dir, char const* name) {
  char* uname = str_copy (name);
  uname[0]    = toupper (name[0]);
  char* abs   = io_absolute (dir);
  char* pdir  = io_parent_path (abs);
  char* cmd =
    str_fmt ("cd %s && dotnet new classlib -n %s --language C#", pdir, uname);
  fprintf (stderr, "%s\n", cmd);
  free (pdir);
  char* oldclass = str_fmt ("%s/Class1.cs", abs);
  char* outclass = str_fmt ("%s/%s.cs", abs, uname);
  char* classcontent =
    str_fmt ("namespace %s;\n\npublic class %s {\n\n}\n", uname, uname);
  free (abs);
  free (uname);
  int r = system (cmd);

  if (!r) {
    FILE* out = fopen (outclass, "w");
    if (out) {
      fwrite (classcontent, 1, strlen (classcontent), out);
      fclose (out);
      io_remove (oldclass);
    }
  }
  free (classcontent);
  free (outclass);
  free (oldclass);


  return r;
}

int sgsharp_build (char const* dir) {
  return 0;
}
