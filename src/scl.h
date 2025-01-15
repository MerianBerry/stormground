#ifndef SCL_H
#define SCL_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct scl_file_s scl_file;

typedef struct scl_file_s {
  void *stream;
} scl_file;

scl_file *scl_open (char const *mode, char const *path);

scl_file *scl_openf (char const *mode, char const *path_fmt, ...);

int scl_read (scl_file *, void *buffer, int n);

int scl_read_malloc (scl_file *, void **buffer, int n);

int scl_write (scl_file *, void const *buffer, int n);

int scl_write_str (scl_file *F, char const *str);

void scl_close (scl_file *);

char const *scl_realpath (char const *rel);

char const *scl_parentpath (char const *path);

int scl_exists (char const *path);

int scl_mkdir (char const *path);

void scl_hide (char const *path);

int scl_chdir (char const *dir);

int scl_utf8_chsize (unsigned char c);

int scl_utf8_strlen (char const *str);

int scl_utf8_actual (char const *str, int ind);

int scl_utf8_at (char const *str, int ind);

unsigned int scl_utf8_encode (int code);

int scl_utf8_decode (unsigned int utf8);

#define XML_FREE_PATCH     0
#define XML_FREE_RECURSIVE 1

typedef struct xml_doc_s  xml_doc;
typedef struct xml_node_s xml_node;
typedef struct xml_attr_s xml_attr;
typedef struct xml_page_s xml_page;

typedef struct xml_attr_s {
  xml_node   *parent;
  xml_attr   *prev;
  xml_attr   *next;
  char const *tag;
  char const *data;
} xml_attr;

typedef struct xml_node_s {
  xml_page   *_page;
  xml_node   *parent;
  xml_node   *prev;
  xml_node   *next;
  xml_node   *_tail;
  xml_node   *child;
  xml_attr   *attr;
  char const *tag;
  char const *data;
  char const *_post;
} xml_node;

typedef struct xml_page_s {
  xml_node *b;
  xml_node *p;
  xml_node *pe;
} xml_page;

typedef struct xml_doc_s {
  xml_page **_pgs;
  xml_node  *root;
  int        _pgc;
} xml_doc;

void xml_free_attr (xml_attr *attr, char mode);

void xml_free_node (xml_node *node, char mode);

void xml_free_doc (xml_doc *doc);

void xml_add_attr (xml_node *node, xml_attr *attr);

void xml_add_node (xml_node *node, xml_node *node2);

void xml_add_child (xml_node *node, xml_node *child);

xml_doc *xml_parse_string (char const *str);


xml_attr *xml_new_str_attr (char const *tag, char const *str);

xml_attr *xml_new_int_attr (char const *tag, int i);

xml_attr *xml_new_float_attr (char const *tag, float n);

xml_node *xml_new_node (xml_doc *doc, char const *tag, char const *str);

xml_node *xml_copy_node (xml_doc *doc, xml_node *node);

void xml_replace_node (xml_node *node, xml_node *with);

void xml_remove_attribute (xml_node *node, char const *tag);

xml_node **xml_xpath (xml_node *from, char const *path);


char const *xml_print (xml_doc *doc);


#ifdef __cplusplus
}
#endif
#endif
