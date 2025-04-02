#include "scl.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  scl_resetclock();
  scl_file *f = scl_open ("r", "xml_big.xml");
  if (f) {
    char const *content;
    int         size = scl_read_malloc (f, (void **)&content, -1);
    if (content) {
      double   cs  = scl_clock();
      xml_doc *doc = xml_parse_string (content);
      double   ce  = scl_clock();
      double   mbs = (double)size / 1048576.0 / (ce - cs);
      if (doc) {
        printf ("%.1fMB file\n%.2fms\n%.1fMB/s\n",
          size / 1048576.0,
          (ce - cs) * 1000.0,
          mbs);
      } else {
        printf ("Failed to parse xml file\n");
      }
      free ((void *)content);
    }
  }
}