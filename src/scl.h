#ifndef SCL_H
#define SCL_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

int scl_mkdir (char const *path);

void scl_hide (char const *path);

int scl_chdir (char const *dir);

char const *scl_execdir();

char const **scl_scanDir (char const *dir, char const *mask, int *count);

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

char scl_strmatch (char const *str, char const *pattern);

typedef struct scl_htab scl_htab;

scl_htab *scl_htabnew();

void scl_htabset (scl_htab *h, char const *key, void const *ptr);

void scl_htabremove (scl_htab *h, char const *key);

void const *scl_htabget (scl_htab const *h, char const *key);

void const *scl_htabnext (scl_htab const *h, char const *key);

scl_htab *scl_htabcopy (scl_htab const *h);

unsigned char scl_log2i (unsigned x);


typedef struct xml_doc_s  xml_doc;
typedef struct xml_page_s xml_page;
typedef struct xml_view_s xml_view;
typedef struct xml_elem_s xml_elem;
typedef struct xml_attr_s xml_attr;

void xml_free_doc (xml_doc *doc);

void xml_add_attr (xml_elem *elem, xml_attr *attr);

void xml_add_elem (xml_elem *elem, xml_elem *child);

xml_doc *xml_parse_string (char const *str);


xml_doc *xml_new_doc();

xml_elem *xml_new_elem (xml_doc *doc, char const *tag, char const *str);

xml_elem *xml_copy_elem (xml_doc *doc, xml_elem *elem);

void xml_replace_elem (xml_elem *elem, xml_elem *with);

xml_attr *xml_str_attribute (char const *tag, char const *str);

xml_attr *xml_int_attribute (char const *tag, int i);

xml_attr *xml_float_attribute (char const *tag, float n);

char const *xml_attribute_as_str (xml_attr *attr);

int xml_attribute_as_int (xml_attr *attr);

float xml_attribute_as_float (xml_attr *attr);

xml_attr *xml_copy_attribute (xml_doc *doc, xml_attr *attr);

xml_attr *xml_find_attribute (xml_elem *elem, char const *tag);

void xml_remove_attribute (xml_elem *elem, char const *tag);

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

#ifdef __cplusplus
}
#endif
#endif
