#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "macl.h"

char const *macl_vfmt (char const *fmt, va_list args) {
  va_list copy;
  va_copy (copy, args);
  int size = vsnprintf (NULL, 0, fmt, copy) + 1;
  va_end (copy);
  char *str = malloc (size);
  vsnprintf (str, size, fmt, args);
  return str;
}

char const *macl_fmt (char const *fmt, ...) {
  char const *msg;
  va_list     args;
  va_start (args, fmt);
  msg = macl_vfmt (fmt, args);
  va_end (args);
  return msg;
}

macl_file *macl_open (char const *mode, char const *path) {
  if (!mode || !path)
    return NULL;
  FILE *stream = fopen (path, mode);
  if (!stream)
    return NULL;
  macl_file *F = (macl_file *)malloc (sizeof (macl_file));
  F->stream    = stream;
  return F;
}

macl_file *macl_openf (char const *mode, char const *path_fmt, ...) {
  va_list args;
  va_start (args, path_fmt);
  char const *path = macl_vfmt (path_fmt, args);
  va_end (args);
  macl_file *r = macl_open (mode, path);
  free ((void *)path);
  return r;
}

int macl_read (macl_file *F, void *buffer, int const n) {
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

int macl_read_malloc (macl_file *F, void **buffer, int const n) {
  if (!buffer)
    return -1;
  int size = macl_read (F, NULL, 0);
  if (size <= 0) {
    (*buffer) = NULL;
    return -1;
  }
  char *buf = (char *)malloc ((size_t)size + 1);
  buf[size] = 0;
  (*buffer) = buf;
  return macl_read (F, buf, n <= 0 ? size : n);
}

int macl_write (macl_file *F, void const *buffer, int const n) {
  if (!F || !F->stream || !buffer || n < 0)
    return -1;
  if (n == 0)
    return 0;
  return fwrite (buffer, 1, n, (FILE *)F->stream);
}

int macl_write_str (macl_file *F, char const *str) {
  return macl_write (F, str, (int)strlen (str));
}

void macl_close (macl_file *F) {
  if (F && F->stream) {
    fclose ((FILE *)F->stream);
    free ((void *)F);
  }
}

char const *macl_realpath (char const *rel) {
  return NULL;
}

char const *macl_parentpath (char const *path) {
  return NULL;
}

int macl_exists (char const *path) {
  return 0;
}

int macl_mkdir (char const *path) {
  return 0;
}

void macl_hide (char const *path) {
}

int macl_chdir (char const *dir) {
  return 0;
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

int mutf8_chsize (BYTE c) {
  if (c >= 0xf0 && c <= 0xf4)
    return 4;
  else if (c >= 0xe0)
    return 3;
  else if (c >= 0xc2)
    return 2;
  return 1;
}

int mutf8_strlen (char const *str) {
  if (!str)
    return -1;
  int s = 0;
  for (int i = 0; i < (int)strlen (str); ++s) {
    int us = mutf8_chsize (((BYTE *)str)[i]);
    i += us;
  }
  return s;
}

int mutf8_actual (char const *str, int ind) {
  if (!str)
    return -1;
  int s = 0;
  for (int i = 0; s < (int)strlen (str) && i < ind; i++) {
    int cs = mutf8_chsize (((BYTE *)str)[s]);
    s += cs;
  }
  return s;
}

int mutf8_at (char const *str, int ind) {
  return 0;
}

unsigned int mutf8_encode (int code) {
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

int mutf8_decode (unsigned int utf8) {
  int                  out     = 0;
  unsigned char const *utf8str = (unsigned char *)&utf8;
  int                  chsize  = mutf8_chsize (utf8str[0]);
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

static char *str_ncopy (char const *str, int n) {
  n          = n >= 0 ? n : 0;
  char *copy = (char *)malloc ((size_t)n + 1);
  copy[n]    = 0;
  if (str)
    memcpy (copy, str, n);
  return copy;
}

static char *str_copy (char const *str) {
  int l = strlen (str ? str : "");
  return str_ncopy (str, l);
}

#define MXML_FREE_ONLY 2

static void mxml_free_attr (mxml_attr *attr, char mode) {
  if (!attr)
    return;
  if (attr->tag)
    free ((void *)attr->tag);
  if (attr->data)
    free ((void *)attr->data);
  if (mode == MXML_FREE_RECURSIVE) {
    if (attr->prev)
      attr->prev->next = NULL;
    for (mxml_attr *i = attr->next; i;) {
      mxml_attr *n = i->next;
      mxml_free_attr (i, MXML_FREE_ONLY);
      free ((void *)i);
      i = n;
    }
    free ((void *)attr);
  } else if (mode == MXML_FREE_PATCH) {
    if (attr->prev)
      attr->prev->next = attr->next;
    if (attr->next)
      attr->next->prev = attr->prev;
    free ((void *)attr);
  }
}

static void mxml_free_node (mxml_node *node, char mode) {
  if (!node)
    return;
  if (node->tag)
    free ((void *)node->tag);
  if (node->data)
    free ((void *)node->data);
  mxml_free_attr (node->attr, 1);
  mxml_free_node (node->child, 1);
  if (mode == MXML_FREE_RECURSIVE) {
    if (node->prev)
      node->prev->next = NULL;
    for (mxml_node *i = node->next; i;) {
      mxml_node *n = i->next;
      mxml_free_node (i, MXML_FREE_ONLY);
      free ((void *)i);
      i = n;
    }
    free ((void *)node);
  } else if (mode == MXML_FREE_PATCH) {
    if (node->prev)
      node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev;
    free ((void *)node);
  }
}

void mxml_add_attr (mxml_node *node, mxml_attr *attr) {
  if (!node || !attr || !attr->tag || !attr->data)
    return;
  attr->parent = node;
  if (!node->attr) {
    node->attr = attr;
    return;
  }
  mxml_attr *i = node->attr;
  for (; i && i->next; i = i->next) {
    if (!strcmp (i->tag, attr->tag)) {
      if (i->prev)
        i->prev->next = attr;
      if (i->next)
        i->next->prev = attr;
      mxml_free_attr (i, MXML_FREE_ONLY);
      free ((void *)i);
      return;
    }
  }
  i->next    = attr;
  attr->prev = i;
}

void mxml_add_node (mxml_node *node, mxml_node *node2) {
  if (!node || !node->tag || !node2 || !node2->tag)
    return;
  node2->parent = node->parent;
  mxml_node *i  = node;
  for (; i && i->next; i = i->next) {
  }
  i->next     = node2;
  node2->prev = i;
}

void mxml_add_child (mxml_node *node, mxml_node *child) {
  if (!node || !node->tag || !child || !child->tag)
    return;
  child->parent = node;
  if (!node->child) {
    node->child = child;
    return;
  }
  mxml_node *i = node->child;
  for (; i && i->next; i = i->next) {
  }
  i->next     = child;
  child->prev = i;
}

#define mxissym(str, i) \
  (isalnum (str[0]) || str[0] == '_' || mutf8_chsize (str[0]) > 1)
#define mxdecode(str, i) mutf8_decode (*(unsigned int *)(&str[i]))
#define mxinc(p)         (p += mutf8_chsize (p[0]))

static unsigned char mxml_parse_char (char const *s, char const **ep) {
  if (s[0] != '\\')
    return s[0];
  switch (s[1]) {
  case '\'':
    return (*ep)++, '\'';
  case '\"':
    return (*ep)++, '\"';
  case '\\':
    return (*ep)++, '\\';
  case 'n':
    return (*ep)++, '\n';
  case 'r':
    return (*ep)++, '\r';
  case 't':
    return (*ep)++, '\t';
  case 'b':
    return (*ep)++, '\b';
  default:
    return (*ep)++, s[1];
  }
}

static char const *mxml_parse_str (char const *s, char const **ep) {
  char const *p = s;
  if (p[0] != '\"')
    return NULL;
  p++;
  s = p;
  while (p[0] != '\"') {
    mxml_parse_char (p, &p);
    p++;
  }
  int len = p - s;
  return ((*ep) = p), str_ncopy (s, len);
}

static mxml_attr *mxml_parse_attr (char const *s, char const **ep) {
  mxml_attr   attr;
  char const *p = s;
  if (!mxissym (p, 0))
    return NULL;
  memset (&attr, 0, sizeof (attr));
  s = p;
  while (mxissym (p, 0)) {
    mxinc (p);
  }
  attr.tag = str_ncopy (s, p - s);
  if (p[0] != '=')
    return NULL;
  p++;
  s         = p;
  attr.data = mxml_parse_str (s, &p);
  if (!attr.data) {
    free ((void *)attr.tag);
    return NULL;
  }
  mxml_attr *copy = (mxml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return ((*ep) = p), copy;
}

static mxml_node *mxml_parse_node (mxml_node *parent, char const *s,
  char const **ep) {
  static int  flags = 0;
  mxml_node   node;
  char const *p = s;
  if (p[0] != '<')
    return NULL;
  memset (&node, 0, sizeof (mxml_node));
  node.parent = parent;
  p++;
  s = p;
  if (p[0] == '/' && parent) {
    p++;
    s = p;
    while (mxissym (p, 0)) {
      mxinc (p);
    }
    if (!strncmp (parent->tag, s, p - s)) {
      return (flags |= 1), ((*ep) = p), NULL;
    } else {
      return NULL;
    }
  } else if (p[0] == '/') { // End tag without a parent
    mxml_free_node (&node, MXML_FREE_ONLY);
    return NULL;
  }
  while (mxissym (p, 0)) {
    mxinc (p);
  }
  node.tag = str_ncopy (s, p - s);
  s        = p;
  while (1) {
    if (p[0] == '/' || p[0] == '>')
      break;
    while (isspace (p[0])) {
      p++;
      s = p;
    }
    if (mxissym (p, 0)) {
      mxml_attr *attr = mxml_parse_attr (s, &p);
      if (!attr) {
        mxml_free_node (&node, MXML_FREE_ONLY);
        return NULL;
      }
      mxml_add_attr (&node, attr);
    }
    p++;
  }
  if (p[0] == '>') {
    p++;
    // TODO: parse node text
    while (p[0] == '<') { // While there are child nodes
      s                = p;
      mxml_node *cnode = mxml_parse_node (&node, p, &p);
      if (!cnode && s == p) { // Error
        mxml_free_node (&node, MXML_FREE_ONLY);
        return NULL;
      } else if ((flags & 1) == 1) { // End tag reached
        break;
      }
      mxml_add_child (&node, cnode);
      if (p[0] == 0)
        break;
      p++;
    }
  } else if (p[0] == '/') {
    p++;
    mxml_node *copy = (mxml_node *)malloc (sizeof (node));
    memcpy (copy, &node, sizeof (node));
    return ((*ep) = p), copy;
  }
  if (p[0] != '>' && p[0] != 0) {
    mxml_free_node (&node, MXML_FREE_ONLY);
    return NULL;
  }
  if ((flags & 1) == 1) {
    flags &= ~1;
  }
  mxml_node *copy = (mxml_node *)malloc (sizeof (node));
  memcpy (copy, &node, sizeof (node));
  return ((*ep) = p), copy;
}

mxml_doc *mxml_parse_string (char const *str) {
  mxml_doc    doc;
  char const *p    = str;
  mxml_node  *root = mxml_parse_node (NULL, str, &p);
  if (!root)
    return NULL;
  memset (&doc, 0, sizeof (doc));
  doc.root       = root;
  mxml_doc *copy = (mxml_doc *)malloc (sizeof (doc));
  memcpy (copy, &doc, sizeof (doc));
  return copy;
}
