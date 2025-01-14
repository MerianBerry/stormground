#ifndef MACL_H
#define MACL_H

#include <stdarg.h>

typedef struct macl_file_s macl_file;

typedef struct macl_file_s {
  void *stream;
} macl_file;

macl_file *macl_open (char const *mode, char const *path);

macl_file *macl_openf (char const *mode, char const *path_fmt, ...);

int macl_read (macl_file *, void *buffer, int n);

int macl_read_malloc (macl_file *, void **buffer, int n);

int macl_write (macl_file *, void const *buffer, int n);

int macl_write_str (macl_file *F, char const *str);

void macl_close (macl_file *);

char const *macl_realpath (char const *rel);

char const *macl_parentpath (char const *path);

int macl_exists (char const *path);

int macl_mkdir (char const *path);

void macl_hide (char const *path);

int macl_chdir (char const *dir);

int mutf8_chsize (unsigned char c);

int mutf8_strlen (char const *str);

int mutf8_actual (char const *str, int ind);

int mutf8_at (char const *str, int ind);

unsigned int mutf8_encode (int code);

int mutf8_decode (unsigned int utf8);

#define MXML_FREE_PATCH     0
#define MXML_FREE_RECURSIVE 1

typedef struct mxml_doc_s  mxml_doc;
typedef struct mxml_node_s mxml_node;
typedef struct mxml_attr_s mxml_attr;

typedef struct mxml_attr_s {
  mxml_node  *parent;
  mxml_attr  *prev;
  mxml_attr  *next;
  char const *tag;
  char const *data;
} mxml_attr;

typedef struct mxml_node_s {
  mxml_node  *parent;
  mxml_node  *prev;
  mxml_node  *next;
  mxml_node  *child;
  mxml_attr  *attr;
  char const *tag;
  char const *data;
} mxml_node;

typedef struct mxml_doc_s {
  mxml_node *root;
} mxml_doc;

mxml_doc *mxml_parse_string (char const *str);
#endif
