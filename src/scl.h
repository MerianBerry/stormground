#ifndef SCL_H
#define SCL_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
#  define SCL_EXPORT __declspec(dllexport)
#else
#  define SCL_EXPORT
#endif

int scl_rand();

#define scl_rand_int(min, max) ((scl_rand() % ((max) - (min) + 1)) + (min))

void scl_srand (int);

typedef struct scl_list {
  void **data;
  int    count;
  int    m;
} scl_list;

int scl_listadd (scl_list *l, void *);

int scl_listrm (scl_list *l, int i);

int scl_listins (scl_list *l, int i, void *);

#define SCL_DEFAULT_PAGE_SIZE 4096

typedef struct scl_page {
  struct scl_page *next_;
  void            *data;
  unsigned         used;
  unsigned         size;
} scl_page;

scl_page *scl_pagenew (unsigned size);

void *scl_pagealloc (scl_page *page, unsigned size);

void scl_freepages (scl_page *page);

typedef struct scl_time {
#if defined(_WIN32)
  long s;
  long c;
#else
  long s;
  long ns;
#endif
} scl_time;

void scl_waitms (double ms);

void scl_resetclock();

// Returns a time point in seconds
double scl_clock();

char const *scl_fmt_static (char const *fmt, ...);

char const *scl_vfmt (char const *fmt, va_list args);

char const *scl_fmt (char const *fmt, ...);

typedef struct scl_file_s scl_file;

typedef struct scl_file_s {
  void *stream;
} scl_file;

scl_file *scl_open (char const *mode, char const *path);

scl_file *scl_openf (char const *mode, char const *path_fmt, ...);

unsigned scl_fsize (scl_file *);

unsigned scl_read (scl_file *, void *buffer, unsigned n);

unsigned scl_read_malloc (scl_file *, void **buffer, unsigned n);

int scl_write (scl_file *, void const *buffer, int n);

int scl_write_str (scl_file *F, char const *str);

void scl_close (scl_file *);

char const *scl_realpath (char const *rel);

char const *scl_parentpath (char const *path);

char const *scl_filename (char const *path);

int scl_exists (char const *path);

int scl_existsf (char const *fmt, ...);

long scl_wtime (char const *path);

int scl_mkdir (char const *path);

void scl_hide (char const *path);

int scl_chdir (char const *dir);

char const *scl_execdir();

char const **scl_scandir (char const *dir, char const *mask, int *count);

char const **scl_glob (char const *dir, char const *mask, int *count);

int scl_utf8_chsize (unsigned char c);

int scl_utf8_strlen (char const *str);

int scl_utf8_actual (char const *str, int ind);

int scl_utf8_at (char const *str, int ind);

unsigned int scl_utf8_encode (int code);

int scl_utf8_decode (unsigned int utf8);

char const *scl_strncopy (char const *str, int n);

char const *scl_strcopy (char const *str);

int scl_strnffi (char const *str, char const *cs, int n);

int scl_strffi (char const *str, char const *cs);

char const *scl_strncat (char const *str, char const *str2, int n, int n2,
                         char freestr);

char const *scl_strcat (char const *str, char const *str2, char freestr);

char const *scl_strncat2 (char *str, char const *str2, int n, int n2);

char const *scl_strcat2 (char *str, char const *str2);

char const *scl_strreplace (char const *str, char const *old, char const *with);

char const *scl_randstr (int len);

char scl_strmatch (char const *str, char const *pattern);

unsigned int scl_strhash (char const *str);

typedef struct scl_htab scl_htab;

scl_htab *scl_htabnew();

void scl_htabset (scl_htab *h, char const *key, void const *ptr);

void scl_htabremove (scl_htab *h, char const *key);

void const *scl_htabget (scl_htab const *h, char const *key);

void const *scl_htabnext (scl_htab const *h, char const *key);

scl_htab *scl_htabcopy (scl_htab const *h);

typedef struct xml_elem_s xml_elem;

typedef struct xml_view_s {
  char *p;
  char *e;
} xml_view;

#define xml_node_fields    \
  xml_view         tag;    \
  xml_view         data;   \
  xml_elem        *parent; \
  struct xml_node *next

typedef struct xml_node {
  xml_node_fields;
} xml_node;

typedef struct xml_attr_s {
  xml_node_fields;
} xml_attr;

#define xml_elem_fields \
  xml_node_fields;      \
  xml_elem *child;      \
  xml_elem *tail;       \
  xml_attr *attr

typedef struct xml_elem_s {
  xml_elem_fields;
} xml_elem;

typedef struct xml_doc_s {
  xml_elem_fields;
  scl_page txt;
  scl_page nodes;
} xml_doc;

void xml_free_doc (xml_doc *doc);

void xml_add_attr (xml_elem *elem, xml_attr *attr);

void xml_add_elem (xml_elem *elem, xml_elem *child);

xml_doc *xml_load_string (char const *str);

xml_doc *xml_load_file (char const *path);

xml_doc *xml_new_doc();

xml_elem *xml_new_elem (xml_doc *doc, char const *tag, char const *str);

xml_elem *xml_copy_elem (xml_doc *doc, xml_elem *elem);

void xml_replace_elem (xml_elem *elem, xml_elem *with);

/*xml_attr *xml_str_attribute (char const *tag, char const *str);

xml_attr *xml_int_attribute (char const *tag, int i);

xml_attr *xml_float_attribute (char const *tag, float n);

char const *xml_attribute_as_str (xml_attr *attr);

int xml_attribute_as_int (xml_attr *attr);

float xml_attribute_as_float (xml_attr *attr);*/

xml_attr *xml_copy_attribute (xml_doc *doc, xml_attr *attr);

xml_attr *xml_find_attribute (xml_elem *elem, char const *tag);

void xml_remove_attribute (xml_elem *elem, char const *tag);

#define xml_tag(n) xml_tag_ ((xml_node *)n)
char const *xml_tag_ (xml_node *n);

#define xml_data(n) xml_data_ ((xml_node *)n)
char const *xml_data_ (xml_node *n);

typedef enum {
  XPATH_RESULT_ELEMENT,
  XPATH_RESULT_ATTR,
  XPATH_RESULT_TEXT,
} xpath_result_type;

typedef struct xpath_result_s {
  xpath_result_type type;

  union {
    xml_elem   *elem;
    xml_attr   *attr;
    char const *text;
  };
} xpath_result;

char const *xml_print (xml_doc *doc);

typedef struct xpath_exp_s xpath_exp;

xpath_exp *xml_xpath (char const *exp);

typedef struct scl_vec2 {
  float x;
  float y;
} scl_vec2;

typedef struct scl_vec3 {
  float x;
  float y;
  float z;
} scl_vec3;

float distance2d (scl_vec2 v);

float distance3d (scl_vec3 v);

float dir2d (scl_vec2 v);

scl_vec2 plus2d (scl_vec2 a, scl_vec2 b);

scl_vec2 sub2d (scl_vec2 a, scl_vec2 b);

scl_vec2 mag2d (scl_vec2 v, float m);

scl_vec2 normalize2d (scl_vec2 v);

scl_vec3 normalize3d (scl_vec3 v);

float dot2d (scl_vec2 a, scl_vec2 b);

float dot3d (scl_vec3 a, scl_vec3 b);

int powi (int x, int y);

float minf (float x, float y);

float maxf (float x, float y);

float clampf (float x, float y, float z);

int mini (int x, int y);

int maxi (int x, int y);

int clampi (int x, int y, int z);

char signf (float x);

float floorf (float x);

float ceilf (float x);

float roundf (float x);

unsigned char log2i (unsigned x);
#ifdef __cplusplus
}
#endif
#endif
