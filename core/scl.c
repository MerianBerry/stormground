#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <io.h>

#include "scl.h"

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  define access _access
#  define F_OK   0
#else
#  include <unistd.h>
#endif

#if defined(_WIN32)
#  ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#    define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#  endif
/* Windows sleep in 100ns units */
static BOOLEAN _nanosleep (LONGLONG ns) {
  // h_loadWinAPI();
  ns /= 100;
  /* Declarations */
  HANDLE        timer; /* Timer handle */
  LARGE_INTEGER li; /* Time defintion */
  /* Create timer */
  if (!(timer = CreateWaitableTimerExW (NULL,
          NULL,
          CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
          TIMER_ALL_ACCESS))) {
    return FALSE;
  }
  /* Set timer properties */
  li.QuadPart = -ns;
  if (!SetWaitableTimer (timer, &li, 0, NULL, NULL, FALSE)) {
    CloseHandle (timer);
    return FALSE;
  }
  /* Start & wait for timer */
  WaitForSingleObject (timer, INFINITE);
  /* Clean resources */
  CloseHandle (timer);
  /* Slept without problems */
  return TRUE;
}
#endif

void scl_waitms (double ms) {
#if defined(__unix__) || defined(__APPLE__)
  h_timepoint s  = timenow();
  timespec_t  ts = {2000, 0};
  ts.tv_sec      = ms / 1000.0;
  ts.tv_nsec     = fmodf (ms, 1000) * 1000000.0;
  while (nanosleep (&ts, &ts) == -1)
    ;
#elif defined(_WIN32)
  LARGE_INTEGER li;
  QueryPerformanceCounter (&li);
  LARGE_INTEGER lf;
  QueryPerformanceFrequency (&lf);
  while (1) {
    LARGE_INTEGER li2;
    QueryPerformanceCounter (&li2);
    if ((double)(li2.QuadPart - li.QuadPart) / (double)lf.QuadPart * 1000.0 >
        ms) {
      break;
    }
    _nanosleep (1000);
  }
#endif
}

static char const *scl_vfmt_static (char const *fmt, va_list args) {
  static char buf[4096];
  va_list     copy;
  int         size = vsnprintf ((void *)buf, sizeof (buf) - 1, fmt, args);
  buf[size]        = 0;
  return buf;
}

static char const *scl_fmt_static (char const *fmt, ...) {
  char const *msg;
  va_list     args;
  va_start (args, fmt);
  msg = scl_vfmt_static (fmt, args);
  va_end (args);
  return msg;
}

char const *scl_vfmt (char const *fmt, va_list args) {
  va_list copy;
  va_copy (copy, args);
  int size = vsnprintf (NULL, 0, fmt, copy) + 1;
  va_end (copy);
  char *str = malloc (size);
  vsnprintf (str, size, fmt, args);
  return str;
}

char const *scl_fmt (char const *fmt, ...) {
  char const *msg;
  va_list     args;
  va_start (args, fmt);
  msg = scl_vfmt (fmt, args);
  va_end (args);
  return msg;
}

scl_file *scl_open (char const *mode, char const *path) {
  if (!mode || !path)
    return NULL;
  FILE *stream = fopen (path, mode);
  if (!stream)
    return NULL;
  scl_file *F = (scl_file *)malloc (sizeof (scl_file));
  F->stream   = stream;
  return F;
}

scl_file *scl_openf (char const *mode, char const *path_fmt, ...) {
  va_list args;
  va_start (args, path_fmt);
  char const *path = scl_vfmt (path_fmt, args);
  va_end (args);
  scl_file *r = scl_open (mode, path);
  free ((void *)path);
  return r;
}

int scl_read (scl_file *F, void *buffer, int const n) {
  if (!F)
    return -1;
  if (!buffer) {
    int off = ftell ((FILE *)F->stream);
    fseek ((FILE *)F->stream, 0, SEEK_END);
    int len = ftell ((FILE *)F->stream);
    fseek ((FILE *)F->stream, off, SEEK_SET);
    return len;
  }
  return fread (buffer, 1, n, (FILE *)F->stream);
}

int scl_read_malloc (scl_file *F, void **buffer, int const n) {
  if (!buffer)
    return -1;
  int size = scl_read (F, NULL, 0);
  if (size <= 0) {
    (*buffer) = NULL;
    return -1;
  }
  char *buf = (char *)malloc ((size_t)size + 1);
  memset (buf, 0, (size_t)size + 1);
  (*buffer) = buf;
  return scl_read (F, buf, n <= 0 ? size : n);
}

int scl_write (scl_file *F, void const *buffer, int const n) {
  if (!F || !F->stream || !buffer || n < 0)
    return -1;
  if (n == 0)
    return 0;
  return fwrite (buffer, 1, n, (FILE *)F->stream);
}

int scl_write_str (scl_file *F, char const *str) {
  return scl_write (F, str, (int)strlen (str));
}

void scl_close (scl_file *F) {
  if (F && F->stream) {
    fclose ((FILE *)F->stream);
    free ((void *)F);
  }
}

char const *scl_realpath (char const *rel) {
  static char fpath[MAX_PATH];
#if defined(_WIN32)
  _fullpath (fpath, rel, MAX_PATH);
#elif defined(__unix__)
  realpath (path, fpath);
#endif
  char *copy = malloc (MAX_PATH);
  memcpy (copy, fpath, MAX_PATH);
  return copy;
}

char const *scl_parentpath (char const *path) {
  if (!path)
    return NULL;
  char const *abs = scl_realpath (path);
  int         l   = strlen (abs);
  char       *p   = (char *)abs + l - 1;
  int         n   = -1;
  for (; *p && p >= abs; --p)
    if (*p == '/' || *p == '\\') {
      while (*p == '/' || *p == '\\')
        p--;
      p++;
      break;
    }
  n               = p - abs;
  char const *out = p != abs ? scl_strncopy (abs, n) : scl_strcopy (".");
  free ((void *)abs);
  return out;
}

int scl_exists (char const *path) {
  char const *abs = scl_realpath (path);
  int         r   = access (abs, F_OK) == 0;
  free ((void *)abs);
  return r;
}

int scl_existsf (char const *fmt, ...) {
  va_list args;
  va_start (args, fmt);
  char const *path = scl_vfmt (fmt, args);
  int         r    = scl_exists (path);
  free ((void *)path);
  va_end (args);
  return r;
}

int scl_mkdir (char const *path) {
#if defined(__unix__) || defined(__APPLE__)
  stat_t      s     = {0};
  char const *npath = scl_realpath (path);
  if (stat (npath, &s) == -1) {
    mkdir (npath, 0755);
    return 1;
  }
#elif defined(_WIN32)
  char const *npath = scl_realpath (path);
  if (CreateDirectoryA (npath, NULL))
    return 1;
#endif
  free ((void *)npath);
  return 0;
}

void scl_hide (char const *path) {
#ifdef _WIN32
  if (!scl_exists (path))
    return;
  char const *npath = scl_realpath (path);
  SetFileAttributes (npath, FILE_ATTRIBUTE_HIDDEN);
  free ((void *)npath);
#endif
}

int scl_chdir (char const *dir) {
#if defined(_WIN32)
  return !SetCurrentDirectory (dir);
#elif defined(__unix__)
  return chdir (dir);
#endif
}

char const *scl_execdir() {
#ifdef _WIN32
  char buf[MAX_PATH + 1];
  memset (buf, 0, sizeof (buf));
  GetModuleFileName (NULL, buf, MAX_PATH);
#else
  char    buf[PATH_MAX];
  ssize_t count = readlink ("/proc/self/exe", buf, PATH_MAX);
#endif
  return scl_parentpath (buf);
}

#ifndef BYTE
#  define BYTE unsigned char
#endif

static int powi (int x, int y) {
  int o = x;
  int i;
  for (i = 0; i < y - 1; ++i) {
    o *= x;
  }
  return o;
}

int scl_utf8_chsize (BYTE c) {
  int o = ((int)c - 0xc2) / 22 + 2;
  return o < 1 ? 1 : o;
}

int scl_utf8_strlen (char const *str) {
  if (!str)
    return -1;
  int s = 0;
  for (int i = 0; i < (int)strlen (str); ++s) {
    int us = scl_utf8_chsize (((BYTE *)str)[i]);
    i += us;
  }
  return s;
}

int scl_utf8_actual (char const *str, int ind) {
  if (!str)
    return -1;
  int s = 0;
  for (int i = 0; s < (int)strlen (str) && i < ind; i++) {
    int cs = scl_utf8_chsize (((BYTE *)str)[s]);
    s += cs;
  }
  return s;
}

int scl_utf8_at (char const *str, int ind) {
  if (!str)
    return -1;

  int out = 0;
  for (; *str && ind > 0; ind--) {
    int s = scl_utf8_chsize (*str);
    str += s;
  }
  memcpy (&out, str, scl_utf8_chsize (*str));
  return out;
}

unsigned int scl_utf8_encode (int code) {
  unsigned int out = 0;
  /* 4 byte */
  if (code > 0xffff) {
    BYTE one = 30 << 3 | code >> 18 & 0x7;
    BYTE two = 2 << 6 | code >> 12 & 0x3f;
    BYTE tre = 2 << 6 | code >> 6 & 0x3f;
    BYTE qua = 2 << 6 | code & 0x3f;
    out      = one | two << 8 | tre << 16 | qua << 24;
  } /* 3 byte */
  else if (code > 0x7ff) {
    BYTE one = 14 << 4 | code >> 12 & 0xf;
    BYTE two = 2 << 6 | code >> 6 & 0x3f;
    BYTE tre = 2 << 6 | code & 0x3f;
    out      = one | two << 8 | tre << 16;
  } /* 2 byte */
  else if (code > 0x7f) {
    BYTE one = 6 << 5 | code >> 6 & 0x1f;
    BYTE two = 2 << 6 | code & 0x3f;
    out      = one | two << 8;
  } /* 1 byte */
  else {
    return code;
  }
  return out;
}

int scl_utf8_decode (unsigned int utf8) {
  int                  out     = 0;
  unsigned char const *utf8str = (unsigned char *)&utf8;
  int                  chsize  = scl_utf8_chsize (utf8str[0]);
  if (chsize == 0)
    return utf8;
  switch (chsize) {
  case 4:
    // sixth
    out |= (utf8str[0] >> 2 & 0x01) << 24;
    // fifth
    out |= ((((utf8str[0] & 0x03) << 2) | ((utf8str[1] >> 4 & 0x03))) & 0x0f)
        << 16;
  case 3:
    // fourth
    out |= ((utf8str[chsize - 3] & 0x0f) << 12);
  case 2:
    // third
    out |= ((utf8str[chsize - 2] >> 2 & 0x0f) << 8);
    // second
    out |= ((((utf8str[chsize - 2] & 0x03) << 2) |
              ((utf8str[chsize - 1] >> 4 & 0x03))) &
             0x0f)
        << 4;
    // first
    out |= (utf8str[chsize - 1] & 0x0f);
    break;
  }
  return out;
}

char const *scl_strncopy (char const *str, int n) {
  n          = n >= 0 ? n : 0;
  char *copy = (char *)malloc ((size_t)n + 1);
  copy[n]    = 0;
  if (str)
    memcpy (copy, str, n);
  return copy;
}

char const *scl_strcopy (char const *str) {
  int l = strlen (str ? str : "");
  return scl_strncopy (str, l);
}

int scl_strnffi (char const *str, char const *cs, int n) {
  if (!str || !cs)
    return -1;
  char const *p   = str;
  int         csl = n;
  for (; *p; p++) {
    if ((n == 1 && *p == *cs) || !strncmp (p, cs, csl))
      return p - str;
  }
  return -1;
}

int scl_strffi (char const *str, char const *cs) {
  if (!str || !cs)
    return -1;
  return scl_strnffi (str, cs, strlen (cs));
}

char const *scl_strncat (char const *str, char const *str2, int n, int n2,
  char freestr) {
  if (!str && !str2)
    return NULL;
  n         = n >= 0 ? n : 0;
  n2        = n2 >= 0 ? n2 : 0;
  char *out = (char *)malloc ((size_t)n + n2 + 1);
  if (str) {
    memcpy (out, str, n);
    if (freestr)
      free ((void *)str);
  }
  if (str2)
    memcpy (&out[n], str2, n2);
  out[n + n2] = 0;
  return out;
}

char const *scl_strcat (char const *str, char const *str2, char freestr) {
  if (!str && !str2)
    return NULL;
  return scl_strncat (str,
    str2,
    strlen (str ? str : ""),
    strlen (str2 ? str2 : ""),
    freestr);
}

char const *scl_strreplace (char const *str, char const *old,
  char const *with) {
  if (!str || !old)
    return NULL;
  char *out = NULL;
  while (1) {
    int         p = scl_strffi (str, old);
    char const *n = scl_strncat (out,
      str,
      strlen (out ? out : ""),
      p >= 0 ? p : strlen (str),
      0);
    if (out)
      free (out);
    if (p < 0) {
      out = (char *)n;
      break;
    }
    if (with) {
      char const *n2 = scl_strcat (n, with, 0);
      free ((void *)n);
      out = (char *)n2;
    } else
      out = (char *)n;
    str += p + strlen (old);
  }
  return out;
}

#define XML_FREE_PATCH     0
#define XML_FREE_RECURSIVE 1
#define XML_FREE_ONLY      2
#define XML_PAGE_SLOTS     1200

#ifdef _MSC_VER
#  define PACK(__Declaration__) \
    __pragma (pack (push, 1)) __Declaration__ __pragma (pack (pop))
#endif

typedef struct xml_view_s {
  char        *p;
  unsigned int l;
} xml_view;

typedef enum {
  XPATH_MATH_POS,
  XPATH_MATH_LAST,
  XPATH_MATH_ETEXT,
  XPATH_MATH_ATTRIBUTE,
  XPATH_ADD,
  XPATH_SUB,
  XPATH_MUL,
  XPATH_DIV,
  XPATH_EQ,
  XPATH_NEQ,
  XPATH_L,
  XPATH_LE,
  XPATH_G,
  XPATH_GE,
  XPATH_EXP_OR,
  XPATH_EXP_AND,
  XPATH_EXP_ETAG,
  XPATH_EXP_ATAG,
  XPATH_EXP_RETAG,
  XPATH_EXP_RATAG,
  XPATH_EXP_MATH,
} xpath_type;

typedef struct xpath_math_s {
  xml_view   tag;
  xml_view   str;
  xpath_type type;
  xpath_type op;
  float      n;
} xpath_math;

typedef struct xpath_exp_s {
  /* for things like "|"/"or" AND "and" */
  struct xpath_exp_s *right;
  /* subdependency */
  struct xpath_exp_s *sub;
  /* right comparison type */
  xpath_type rtype;
  /* exp type */
  xpath_type type;

  union {
    /* copare tag */
    xml_view tag;
    /* math */
    xpath_math math;
  };
} xpath_exp;

typedef struct xml_attr_s {
  xml_elem *parent;
  xml_attr *prev;
  xml_attr *next;
  xml_view  tag;
  xml_view  data;
} xml_attr;

typedef struct xml_elem_s {
  xml_elem *parent;
  xml_elem *prev;
  xml_elem *next;
  xml_elem *_tail;
  xml_elem *child;
  xml_attr *attr;
  xml_view  tag;
  xml_view  data;
  xml_view  _post;
} xml_elem;

typedef struct xml_page_s {
  xml_elem *b;
  xml_elem *p;
  xml_elem *pe;
} xml_page;

typedef struct xml_doc_s {
  char const  *ob;
  unsigned int obl;
  char        *mb;
  char        *mbp;
  unsigned int mbl;
  xml_view    *mh;
  xml_view    *mt;

  xml_elem *root;
} xml_doc;

#define xview(_p, _l) ((xml_view){.p = (char *)(_p), .l = (unsigned int)(_l)})

static int xml_viewcmp (xml_view *sv, xml_view *sv2) {
  if (!sv->p || !sv2->p)
    return 1;
  unsigned int l1 = sv->l;
  unsigned int l2 = sv2->l;
  unsigned int l  = l1 < l2 ? l1 : l2;
  for (unsigned int i = 0; i < l; i++) {
    if (sv->p[i] != sv2->p[i])
      return 1;
  }
  if (l1 - l2 != 0)
    return 1;
  return 0;
}

static int xml_viewstrncmp (xml_view view, char const *str, int n) {
  if (!view.p || !str)
    return 1;
  unsigned int l1 = view.l;
  unsigned int l2 = n;
  unsigned int l  = l1 < l2 ? l1 : l2;
  for (unsigned int i = 0; i < l; i++) {
    if (view.p[i] != str[i])
      return 1;
  }
  if (l1 - l2 != 0)
    return 1;
  return 0;
}

static int xml_viewstrcmp (xml_view view, char const *str) {
  if (!view.p || !str)
    return 1;
  return xml_viewstrncmp (view, str, strlen (str));
}

static void xml_free_attr (xml_attr *attr, char mode) {
  if (!attr)
    return;
  attr->tag.p  = NULL;
  attr->data.p = NULL;
  if (mode == XML_FREE_RECURSIVE) {
    if (attr->prev)
      attr->prev->next = NULL;
    for (xml_attr *i = attr->next; i;) {
      xml_attr *n = i->next;
      xml_free_attr (i, XML_FREE_ONLY);
      free ((void *)i);
      i = n;
    }
    free ((void *)attr);
  } else if (mode == XML_FREE_PATCH) {
    if (attr->prev)
      attr->prev->next = attr->next;
    if (attr->next)
      attr->next->prev = attr->prev;
    free ((void *)attr);
  }
}

static void xml_free_elem (xml_elem *elem, char mode) {
  if (!elem)
    return;
  xml_free_attr (elem->attr, 1);
  xml_free_elem (elem->child, 1);
  if (mode == XML_FREE_RECURSIVE) {
    if (elem->prev)
      elem->prev->next = NULL;
    for (xml_elem *i = elem->next; i;) {
      xml_elem *n = i->next;
      xml_free_elem (i, XML_FREE_ONLY);
      free ((void *)i);
      i = n;
    }
  } else if (mode == XML_FREE_PATCH) {
    if (elem->prev)
      elem->prev->next = elem->next;
    if (elem->next)
      elem->next->prev = elem->prev;
    free ((void *)elem);
  } else {
    return;
  }
  free ((void *)elem);
}

void xml_free_doc (xml_doc *doc) {
  if (!doc)
    return;
  xml_free_elem (doc->root, XML_FREE_RECURSIVE);
  free ((void *)doc);
}

/*static void xml_page_add (xml_doc *doc) {
  if (!doc)
    return;
  xml_page **npages =
    (xml_page **)malloc (sizeof (xml_page *) * (doc->_pgc + 1));
  if (doc->_pgs) {
    memcpy (npages, doc->_pgs, sizeof (xml_page *) * doc->_pgc);
    free ((void *)doc->_pgs);
  }
  xml_page *page = (xml_page *)malloc (sizeof (xml_page));
  page->b        = (xml_elem *)malloc (sizeof (xml_elem) * XML_PAGE_SLOTS);
  memset (page->b, 0, sizeof (xml_elem) * XML_PAGE_SLOTS);
  page->p           = page->b;
  page->pe          = page->b + XML_PAGE_SLOTS;
  npages[doc->_pgc] = page;
  doc->_pgs         = npages;
  doc->_pgc++;
}

static xml_elem *xml_page_slot (xml_doc *doc) {
  if (!doc)
    return NULL;
  for (int i = doc->_pgc - 1; i >= 0; i--) {
    xml_page *page = doc->_pgs[i];
    if (page->p < page->pe) {
      xml_elem *slot = page->p;
      slot->_page    = page;
      for (++page->p; page->p < page->pe && page->p->_page; page->p++) {
      }
      return slot;
    }
  }
  xml_page_add (doc);
  return xml_page_slot (doc);
}*/

void xml_add_root (xml_doc *doc, xml_elem *elem) {
  if (!doc || !elem)
    return;
  if (doc->root)
    xml_free_elem (doc->root, XML_FREE_RECURSIVE);
  doc->root    = elem;
  elem->parent = NULL;
}

void xml_add_attr (xml_elem *elem, xml_attr *attr) {
  if (!elem || !attr || !attr->tag.p || !attr->data.p)
    return;
  attr->parent = elem;
  if (elem->attr) {
    xml_attr *i = elem->attr;
    for (; i && i->next; i = i->next) {
      if (!xml_viewcmp (&i->tag, &attr->tag)) {
        i->data = attr->data;
        xml_free_attr (attr, XML_FREE_ONLY);
        return;
      }
    }
    i->next    = attr;
    attr->prev = i;
  } else
    elem->attr = attr;
}

void xml_add_elem (xml_elem *elem, xml_elem *elem2) {
  if (!elem || !elem2)
    return;
  elem2->parent = elem->parent;
  if (elem->_tail)
    elem->_tail->next = elem2, elem2->prev = elem->_tail, elem->_tail = elem2;
  else
    elem->next = elem2, elem->_tail = elem2;
}

void xml_add_child (xml_elem *elem, xml_elem *child) {
  if (!elem || !child)
    return;
  child->parent = elem;
  if (elem->child)
    xml_add_elem (elem->child, child);
  else
    elem->child = child;
}

#define xisalnum(c) \
  (((c & 64) && ((c - 'A') & 31) <= 25) || (c >= '0' && c <= '9'))
#define xisdigit(c) (c >= '0' && c <= '9')
#define xisspace(c) (c == ' ' || c == '\n' || c == '\r')

#define xissym(c)   (xisalnum (c) || c == '_' || ((unsigned char)c & 0x80))

static int xml_parse_textchar (char const *s, char const **ep, char *out) {
  if (*s != '&') {
    return ((*ep)++), (*out = *s), 1;
  } else {
    if (!strncmp (s, "&lt;", 4))
      return ((*ep) += 4), (*out = '<'), 1;
    if (!strncmp (s, "&gt;", 4))
      return ((*ep) += 4), (*out = '>'), 1;
    if (!strncmp (s, "&amp;", 5))
      return ((*ep) += 5), (*out = '&'), 1;
    if (!strncmp (s, "&apos;", 6))
      return ((*ep) += 6), (*out = '\''), 1;
    if (!strncmp (s, "&quot;", 6))
      return ((*ep) += 6), (*out = '\"'), 1;
    return ((*ep)++), 1;
  }
}

static xml_view xml_parse_text (char const *s, char const **ep, char delim) {
  char const *p = s;
  while (*p && *p != delim)
    p++;
  return ((*ep) = p), xview (s, p - s);
}

static xml_attr *xml_parse_attr (char const *s, char const **ep) {
  xml_attr    attr;
  char const *p = s;
  if (!xissym (*p))
    return NULL;
  memset (&attr, 0, sizeof (attr));
  do
    p++;
  while (xissym (*p));
  attr.tag = xview (s, p - s);
  if (p[0] != '=' && p[1] != '\"' && p[1] != '\'')
    return NULL;
  char delim = p[1];
  s          = (p += 2);
  attr.data  = xml_parse_text (s, &p, delim);
  return ((*ep) = ++p), xml_copy_attribute (&attr);
}

static xml_elem *xml_parse_elem (xml_doc *doc, xml_elem *parent, char const *s,
  char const **ep) {
  static int  leave = 0;
  xml_elem    elem;
  char const *p = s;
  if (*p != '<')
    return NULL;
  memset (&elem, 0, sizeof (xml_elem));
  elem.parent = parent;
  s           = ++p;
  if (xissym (*p)) {
    do
      p++;
    while (xissym (*p));
    elem.tag = xview (s, p - s);
    while (xisspace (*p)) {
      do
        p++;
      while (xisspace (*p));
      xml_attr *attr = xml_parse_attr (p, &p);
      if (attr)
        xml_add_attr (&elem, attr);
      else
        return xml_free_elem (&elem, XML_FREE_ONLY), NULL;
    }
    if (*p == '>') {
      p++;
      if (xissym (*p) || xisspace (*p)) {
        elem.data = xml_parse_text (p, &p, '<');
      }
      while (*p == '<') { // While there are child elems
        s               = p;
        xml_elem *celem = xml_parse_elem (doc, &elem, p, &p);
        if (celem && !leave)
          xml_add_child (&elem, celem);
        else if (leave)
          break;
        else if (!celem)
          return xml_free_elem (&elem, XML_FREE_ONLY), NULL;
      }
    }
    if (*p == '/' || leave) {
      p += 1 + (*p == '/');
      leave = 0;
      s     = p;
      while (xisspace (*p) && elem._post.l < 63) {
        elem._post.p = (char *)s;
        elem._post.l++;
        p++;
      }
      return ((*ep) = p), xml_copy_elem (&elem);
    } else // Is a parent, but ended before being terminated
      return xml_free_elem (&elem, XML_FREE_ONLY), NULL;
  } else if (*p == '/') {
    if (parent) {
      s = ++p;
      while (xissym (*p))
        p++;
      xml_view tv = xview (s, p - s);
      if (!xml_viewcmp (&parent->tag, &tv))
        return (leave |= 1), ((*ep) = p), NULL;
      else
        return NULL;
    } else
      return NULL;
  } else if (*p == '?') {
    if (!parent) { // ordered like this for branch opt
      p++;
      while (p[0] && p[0] != '?' && p[1] != '>')
        p++;
      if (p[1] == '>')
        return p += 2, xml_parse_elem (doc, NULL, p, ep);
      else
        return NULL;
    } else
      return NULL;
  }
  return NULL;
}

xml_doc *xml_parse_string (char const *str) {
  xml_doc     doc;
  char const *p = str;
  memset (&doc, 0, sizeof (doc));
  doc.ob  = scl_strcopy (str);
  doc.obl = strlen (str);
  // xml_page_add (&doc);
  xml_elem *root = xml_parse_elem (&doc, NULL, doc.ob, &p);
  if (!root)
    return NULL;
  doc.root      = root;
  xml_doc *copy = (xml_doc *)malloc (sizeof (xml_doc));
  memcpy (copy, &doc, sizeof (xml_doc));
  copy->ob = doc.ob;
  return copy;
}

xml_doc *xml_new_doc() {
  xml_doc *doc = malloc (sizeof (xml_doc));
  memset (doc, 0, sizeof (xml_doc));
  return doc;
}

xml_elem *xml_new_elem (xml_doc *doc, char const *tag, char const *str) {
  if (!tag)
    return NULL;
  xml_elem elem;
  memset (&elem, 0, sizeof (elem));
  elem.tag.p = (char *)scl_strcopy (tag);
  elem.tag.l = strlen (tag);
  if (str) {
    elem.data.p = (char *)scl_strcopy (str);
    elem.data.l = strlen (str);
  }
  return memcpy (malloc (sizeof (xml_elem)), &elem, sizeof (elem));
}

xml_elem *xml_copy_elem (xml_elem *elem) {
  if (!elem)
    return NULL;
  return memcpy (malloc (sizeof (xml_elem)), elem, sizeof (xml_elem));
}

xml_elem **xml_find_elems (xml_elem *from, char const *tag, xml_find_mode mode,
  int *count) {
  return NULL;
}

void xml_replace_elem (xml_elem *elem, xml_elem *with) {
  if (!elem)
    return;
  if (with) {
    with->parent = elem->parent;
    with->prev   = elem->prev;
    with->next   = elem->next;
    if (elem->prev)
      elem->prev->next = with;
    if (elem->next)
      elem->next->prev = with;
    xml_free_elem (elem, XML_FREE_ONLY);
  } else {
    xml_free_elem (elem, XML_FREE_PATCH);
  }
}

xml_attr *xml_str_attribute (char const *tag, char const *str) {
  if (!tag || !str)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag.p     = (char *)scl_strcopy (tag);
  attr.tag.l     = strlen (tag);
  attr.data.p    = (char *)scl_strcopy (str);
  attr.data.l    = strlen (str);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_int_attribute (char const *tag, int i) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag.p     = (char *)scl_strcopy (tag);
  attr.tag.l     = strlen (tag);
  attr.data.p    = (char *)scl_fmt ("%i", i);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_float_attribute (char const *tag, float n) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag.p     = (char *)scl_strcopy (tag);
  attr.tag.l     = strlen (tag);
  attr.data.p    = (char *)scl_fmt ("%f", n);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_copy_attribute (xml_attr *attr) {
  if (!attr)
    return NULL;
  xml_attr *copy = (xml_attr *)malloc (sizeof (xml_attr));
  memcpy (copy, attr, sizeof (xml_attr));
  return copy;
}

xml_attr *xml_find_attribute (xml_elem *elem, char const *tag) {
  if (!elem || !elem->attr || !tag)
    return NULL;
  xml_view tv = xview (tag, strlen (tag));
  for (xml_attr *attr = elem->attr; attr; attr = attr->next)
    if (!xml_viewcmp (&attr->tag, &tv))
      return attr;
  return NULL;
}

void xml_remove_attribute (xml_elem *elem, char const *tag) {
  if (!elem || !elem->attr)
    return;
  xml_attr *attr = xml_find_attribute (elem, tag);
  if (attr)
    xml_free_attr (attr, XML_FREE_PATCH);
}

static void xml_checkset (char **out, char **wp, int *size, int nlen,
  int astep) {
  if (*wp - *out + nlen < *size - 1) {
    return;
  } else {
    for (; nlen >= 0; nlen -= astep) {
      int   off  = *wp - *out;
      char *nout = (char *)malloc ((size_t)(*size) + astep);
      memset (nout, 0, (size_t)(*size) + astep);
      memcpy (nout, *out, *size);
      free ((void *)*out);
      *out = nout;
      *size += astep;
      *wp = nout + off;
    }
  }
}

#define xml_app_free(out, wp, size, str)         \
  {                                              \
    char *__text = (char *)str;                  \
    int   __tlen = strlen (__text);              \
    xml_checkset (out, wp, size, __tlen, 32768); \
    memcpy (*wp, __text, __tlen);                \
    free ((void *)__text);                       \
    *wp += __tlen;                               \
  }
#define xml_app(out, wp, size, str)              \
  {                                              \
    char *__text = (char *)str;                  \
    int   __tlen = strlen (__text);              \
    xml_checkset (out, wp, size, __tlen, 32768); \
    memcpy (*wp, __text, __tlen);                \
    *wp += __tlen;                               \
  }
#define xml_napp(out, wp, size, str, max)        \
  {                                              \
    char *__text = (char *)str;                  \
    int   __tlen = max;                          \
    xml_checkset (out, wp, size, __tlen, 32768); \
    memcpy (*wp, __text, __tlen);                \
    *wp += __tlen;                               \
  }

static int xml_print_string (xml_view v, char **out, char **wp, int *size,
  char keepquot) {
  char *p = (char *)v.p;
  for (; p != v.p + v.l; p++) {
    if (*p == '<') {
      xml_napp (out, wp, size, "&lt;", 4);
    } else if (*p == '>') {
      xml_napp (out, wp, size, "&gt;", 4);
    } else if (*p == '&') {
      xml_napp (out, wp, size, "&amp;", 5);
    } else if (*p == '\'') {
      xml_napp (out, wp, size, "&apos;", 6);
    } else if (*p == '\"' && !keepquot) {
      xml_napp (out, wp, size, "&quot;", 6);
    } else if (*p == '\"') {
      xml_napp (out, wp, size, "\"", 1);
    } else
      xml_napp (out, wp, size, p, 1);
  }
  return 1;
}

static int xml_print_attr (xml_attr *attr, char **out, char **wp, int *size) {
  if (!attr)
    return 0;
  char        noapos    = scl_strnffi (attr->data.p, "\'", attr->data.l) == -1;
  char        noquot    = scl_strnffi (attr->data.p, "\"", attr->data.l) == -1;
  char        aposdelim = (noapos && !noquot) ? 1 : 0;
  char const *q         = !aposdelim ? "\"" : "\'";
  char const *q2        = !aposdelim ? "=\"" : "=\'";
  xml_napp (out, wp, size, " ", 1);
  xml_napp (out, wp, size, attr->tag.p, attr->tag.l);
  xml_napp (out, wp, size, q2, 2);
  xml_print_string (attr->data, out, wp, size, aposdelim);
  xml_napp (out, wp, size, q, 1);
  return 1;
}

static int xml_print_elem (xml_elem *elem, char **out, char **wp, int *size,
  char isroot) {
  if (!elem)
    return 0;
  xml_elem *ielem = elem;
  for (; ielem && ielem->tag.p; ielem = ielem->next) {
    xml_napp (out, wp, size, "<", 1);
    xml_napp (out, wp, size, ielem->tag.p, ielem->tag.l);
    if (ielem->attr) {
      xml_attr *attr = ielem->attr;
      for (; attr; attr = attr->next)
        xml_print_attr (attr, out, wp, size);
    }
    if (ielem->child || isroot || ielem->data.p) {
      xml_napp (out, wp, size, ">", 1);
      if (ielem->data.p)
        xml_print_string (ielem->data, out, wp, size, 0);
      xml_print_elem (ielem->child, out, wp, size, 0);
      xml_napp (out, wp, size, "</", 2);
      xml_napp (out, wp, size, ielem->tag.p, ielem->tag.l);
      xml_napp (out, wp, size, ">", 1);
    } else {
      xml_napp (out, wp, size, "/>", 2);
    }
    if (ielem->_post.p)
      xml_napp (out, wp, size, ielem->_post.p, ielem->_post.l);
  }
  return 1;
}

char const *xml_print (xml_doc *doc) {
  if (!doc || !doc->root)
    return NULL;

  // char const prologue[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  char const prologue[] = "";
  int        size       = 512;
  char      *out        = (char *)malloc (size);
  memset (out, 0, size);
  memcpy (out, prologue, sizeof (prologue) - 1);
  char *wp = out + sizeof (prologue) - 1;
  xml_print_elem (doc->root, &out, &wp, &size, 1);
  return out;
}


#if 0
static xml_elem **xml_xpath_stage (xml_elem *root, xml_view path,
  char const *cond) {
  int   docond = 0;
  int   any    = 0;
  char *p      = path.p + 1;
  char *s      = p;
get_path:
  while (*p != '/' && *p != '[' && *p)
    p++;
  if (p == s && *p == '/') { // path is // (any)
    any = 1, ++s, ++p;
    goto get_path;
  }
  if (*p == '[') // reached condition statment
    docond = 1;
  xml_view v = (xml_view){.n = NULL, .p = s, .l = p - s};
  for (xml_elem *elem = root; elem; elem = elem->next) {
    /* if any is true, match by any means until the first actual match */
    if (!xml_viewcmp (&elem->tag, &v)) {
      if (any) {
      } else {
      }
    } else if (any) {
      xml_xpath_stage (elem, (xml_view){.n = NULL, .p = s, .l = p - s}, cond);
    }
  }
}

xml_elem **xml_xpath (xml_elem *from, char const *path) {
  if (!from || !path || (*path != '/'))
    return NULL;
  int p = scl_strffi (path, "[");
  p     = p > -1 ? p : strlen (path);
  if (p < 2)
    return NULL;
  char const *epath = scl_strncopy (path, p);

  /*
    decompose xpath into conditions
    new path are selected if they meet the criteria from their iteration
    then use an recursive evaluation for each path in the previous stage

    example: /a/b[1]
    root stage:
      root/a/b[1] is chosen because it meets /a/b[1]
    stage:
      there are no more stages, return root/a/b/[1]

    example /a/b[1]/c[@d='e']
    root stage:
      root/a/b[1] meets /a/b/[1]
    stage:
      root/a/b[1]/c[1]
      root/a/b[1]/c[3]
      root/a/b[1]/c[4] all have attr d equal "e"
    stage:
      there are no more stages return evals from stage 2

    example //c[1]
    root:
      root/a/b[1]/c[1] meets //c[1]
      root/a/b[2]/c[1] meets //c[1]

    example //c[@d='e']
      root/a/b[1]/c[1]
      root/a/b[1]/c[3]
      root/a/b[1]/c[4]
      root/a/b[2]/c[1]
      root/a/b[2]/c[3]
      root/a/b[2]/c[4] all have attr d equal "e"
  */

  int        size  = 10;
  xml_elem **paths = (xml_elem **)malloc (sizeof (xml_elem *) * size);
  memset (paths, 0, sizeof (xml_elem *) * size);
  return paths;
}
#endif


static void xpath_tag (xml_view *view, char **s, char **p) {
  char *s2 = *s, *p2 = *p;
  // Skip to tag start
  s2 = ++p2;
  while (xissym (*p2) || (*p2 == '*' && *(p2 - 1) != '*'))
    p2++;
  xml_view v = xview (s2, p2 - s2);
  if (xml_viewstrncmp (v, "*", 1)) {
    *view = v;
  }
  *s = s2;
  *p = p2;
  // e.tag is already null for * case
}

// If calling this externally, set `up` to NULL
xpath_exp *xml_xpath (char const *exp, xpath_exp *up) {
  char     *s = (char *)exp, *p = (char *)exp;
  xpath_exp e;
  memset (&e, 0, sizeof (e));
  // Path exp
  if (*exp == '/') {
    // Post attr paths are forbidden
    if (up && (up->type == XPATH_EXP_ATAG || up->type == XPATH_EXP_RATAG))
      return NULL;
    if (exp[1] != '/') {
      // Element
      if (exp[1] != '@') {
        e.type = XPATH_EXP_ETAG;
        xpath_tag (&e.tag, &s, &p);
        goto post_exp;
        // Attribute
      } else {
        // NOTE matching attributes are forbidden from using math exps
        // and any further path matches are also forbidden
        e.type = XPATH_EXP_ATAG;
        ++s, ++p; // to skip @
        xpath_tag (&e.tag, &s, &p);
        goto post_exp;
      }
    } else { // Recursive match
      ++s, ++p;
      // Element
      if (exp[2] != '@') {
        e.type = XPATH_EXP_RETAG;
        xpath_tag (&e.tag, &s, &p);
        goto post_exp;
        // Attribute
      } else {
        // NOTE matching attributes are forbidden from using math exps
        // and any further path matches are also forbidden
        e.type = XPATH_EXP_RATAG;
        ++s, ++p; // to skip @
        xpath_tag (&e.tag, &s, &p);
        goto post_exp;
      }
    }
    // Math exp
  } else if (*p == '[') {
    xpath_math math;
    memset (&math, 0, sizeof (math));
    e.type = XPATH_EXP_MATH;
    // Macro or element
    if (xissym (p[1])) {
      // Attribute
    } else if (p[1] == '@') {
      math.type = XPATH_MATH_ATTRIBUTE;
      ++s, ++p;
      xpath_tag (&math.tag, &s, &p);
      if (*p == '=') {
        math.op = XPATH_EQ;
      } else if (*p == '<' && p[1] == '=') {
        math.op = XPATH_LE;
        ++p;
      } else if (*p == '>' && p[1] == '=') {
        math.op = XPATH_GE;
        ++p;
      } else if (*p == '<') {
        math.op = XPATH_L;
      } else if (*p == '>') {
        math.op = XPATH_G;
      }
      s = ++p;
      if (xisdigit (*p)) {
        int dot = 0;
        do
          ++p;
        while (xisdigit (*p) || (!dot && (dot = *p == '.')));
        char const *tmp = scl_strncopy (s, p - s);
        math.n          = atof (tmp);
        free ((void *)tmp);
      } else if (*p == '\'' || *p == '\"' && math.op == XPATH_EQ) {
      }

      // Index
    } else if (xisdigit (p[1])) {
      int dot   = 0;
      math.op   = XPATH_EQ;
      math.type = XPATH_MATH_POS;
      ++s, ++p;
      do
        ++p;
      while (xisdigit (*p) || (!dot && (dot = *p == '.')));
      // Invalid math exp
      if (*p != ']' && *p != ' ')
        return NULL;
      char const *tmp = scl_strncopy (s, p - s);
      math.n          = atof (tmp);
      free ((void *)tmp);
      // Invalid index
      if (math.n == 0.f)
        return NULL;
      e.math = math;
      goto post_exp;
    }
  }

post_exp:
  if (*p)
    xml_xpath (p, &e);
  xpath_exp *copy = (xpath_exp *)malloc (sizeof (e));
  memcpy (copy, &e, sizeof (e));
  if (up)
    up->sub = copy;
  else
    return copy;

  return NULL;
}

void xml_eval (xpath_exp *xpath) {
}
