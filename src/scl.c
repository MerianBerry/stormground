#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "scl.h"

static char const *scl_vfmt_static (char const *fmt, va_list args) {
  static char buf[8192];
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
  return NULL;
}

char const *scl_parentpath (char const *path) {
  return NULL;
}

int scl_exists (char const *path) {
  return 0;
}

int scl_mkdir (char const *path) {
  return 0;
}

void scl_hide (char const *path) {
}

int scl_chdir (char const *dir) {
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
  return 0;
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

static char *scl_strncopy (char const *str, int n) {
  n          = n >= 0 ? n : 0;
  char *copy = (char *)malloc ((size_t)n + 1);
  copy[n]    = 0;
  if (str)
    memcpy (copy, str, n);
  return copy;
}

static char *scl_strcopy (char const *str) {
  int l = strlen (str ? str : "");
  return scl_strncopy (str, l);
}

static int scl_strffi (char const *str, char const *cs) {
  if (!str || !cs)
    return -1;
  char const *p   = str;
  int         csl = strlen (cs);
  for (; *p; p++) {
    if (!strncmp (p, cs, csl))
      return p - str;
  }
  return -1;
}

static int scl_strnffi (char const *str, char const *cs, int max) {
  if (!str || !cs)
    return -1;
  char const *p   = str;
  int         csl = max;
  for (; *p; p++) {
    if (!strncmp (p, cs, csl))
      return p - str;
  }
  return -1;
}

static char const *scl_strnappend (char const *str, char const *str2, int n,
  int n2, char freestr) {
  if (!str && !str2)
    return NULL;
  n         = n >= 0 ? n : 0;
  n2        = n2 >= 0 ? n2 : 0;
  int l1    = strlen (str ? str : "");
  l1        = n < l1 ? n : l1;
  int l2    = strlen (str2 ? str2 : "");
  l2        = n2 < l2 ? n2 : l2;
  char *out = (char *)malloc ((size_t)l1 + l2 + 1);
  if (str) {
    memcpy (out, str, l1);
    if (freestr)
      free ((void *)str);
  }
  if (str2)
    memcpy (&out[l1], str2, l2);
  out[l1 + l2] = 0;
  return out;
}

static char const *scl_strappend (char const *str, char const *str2,
  char freestr) {
  if (!str && !str2)
    return NULL;
  int   l1  = strlen (str ? str : "");
  int   l2  = strlen (str2 ? str2 : "");
  char *out = (char *)malloc ((size_t)l1 + l2 + 1);
  if (str) {
    memcpy (out, str, l1);
    if (freestr)
      free ((void *)str);
  }
  if (str2)
    memcpy (&out[l1], str2, l2);
  out[l1 + l2] = 0;
  return out;
}

static char const *scl_strreplace (char const *str, char const *old,
  char const *new) {
  if (!str || !old)
    return NULL;
  char *out = NULL;
  while (1) {
    int         p = scl_strffi (str, old);
    char const *n = scl_strnappend (out,
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
    if (new) {
      char const *n2 = scl_strappend (n, new, 0);
      free ((void *)n);
      out = (char *)n2;
    } else
      out = (char *)n;
    str += p + strlen (old);
  }
  return out;
}

#define XML_FREE_ONLY  2
#define XML_PAGE_SLOTS 1200

void xml_free_attr (xml_attr *attr, char mode) {
  if (!attr)
    return;
  if (attr->tag)
    free ((void *)attr->tag);
  if (attr->data)
    free ((void *)attr->data);
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

void xml_free_node (xml_node *node, char mode) {
  if (!node || !node->_page)
    return;
  if (node->tag)
    free ((void *)node->tag);
  if (node->data)
    free ((void *)node->data);
  if (node->_post)
    free ((void *)node->_post);
  xml_free_attr (node->attr, 1);
  xml_free_node (node->child, 1);
  if (mode == XML_FREE_RECURSIVE) {
    if (node->prev)
      node->prev->next = NULL;
    for (xml_node *i = node->next; i;) {
      xml_node *n = i->next;
      xml_free_node (i, XML_FREE_ONLY);
      // free ((void *)i);
      i = n;
    }
  } else if (mode == XML_FREE_PATCH) {
    if (node->prev)
      node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev;
    // free ((void *)node);
  } else {
    // return;
  }
  node->_page->p = node;
  memset (node, 0, sizeof (xml_node));
  // free ((void *)node);
}

void xml_free_doc (xml_doc *doc) {
  if (!doc)
    return;
  xml_free_node (doc->root, XML_FREE_RECURSIVE);
  free ((void *)doc);
}

static void xml_page_add (xml_doc *doc) {
  if (!doc)
    return;
  xml_page **npages =
    (xml_page **)malloc (sizeof (xml_page *) * (doc->_pgc + 1));
  if (doc->_pgs) {
    memcpy (npages, doc->_pgs, sizeof (xml_page *) * doc->_pgc);
    free ((void *)doc->_pgs);
  }
  xml_page *page = (xml_page *)malloc (sizeof (xml_page));
  page->b        = (xml_node *)malloc (sizeof (xml_node) * XML_PAGE_SLOTS);
  memset (page->b, 0, sizeof (xml_node) * XML_PAGE_SLOTS);
  page->p           = page->b;
  page->pe          = page->b + XML_PAGE_SLOTS;
  npages[doc->_pgc] = page;
  doc->_pgs         = npages;
  doc->_pgc++;
}

static xml_node *xml_page_slot (xml_doc *doc) {
  if (!doc)
    return NULL;
  for (int i = doc->_pgc - 1; i >= 0; i--) {
    xml_page *page = doc->_pgs[i];
    if (page->p < page->pe) {
      xml_node *slot = page->p;
      slot->_page    = page;
      for (++page->p; page->p < page->pe && page->p->_page; page->p++) {
      }
      return slot;
    }
  }
  xml_page_add (doc);
  return xml_page_slot (doc);
}

void xml_add_attr (xml_node *node, xml_attr *attr) {
  if (!node || !attr || !attr->tag || !attr->data)
    return;
  // attr->hash   = KR_v2_hash (attr->tag);
  attr->parent = node;
  if (node->attr) {
    xml_attr *i = node->attr;
    for (; i && i->next; i = i->next) {
      if (!strcmp (i->tag, attr->tag)) {
        free ((void *)i->data);
        i->data = attr->data;
        free (attr);
        return;
      }
    }
    i->next    = attr;
    attr->prev = i;
  } else
    node->attr = attr;
}

void xml_add_node (xml_node *node, xml_node *node2) {
  if (!node || !node->tag || !node2 || !node2->tag)
    return;
  node2->parent = node->parent;
  if (node->_tail)
    node->_tail->next = node2, node2->prev = node->_tail, node->_tail = node2;
  else
    node->next = node2, node->_tail = node2;
}

void xml_add_child (xml_node *node, xml_node *child) {
  if (!node || !node->tag || !child || !child->tag)
    return;
  child->parent = node;
  if (node->child)
    xml_add_node (node->child, child);
  else
    node->child = child;
}

#define mxissym(str) \
  (((unsigned char)*str > 0x7f) || isalnum (*str) || *str == '_')
#define mxdecode(str, i) scl_utf8_decode (*(unsigned int *)(&str[i]))
#define mxinc(p)         (p += scl_utf8_chsize (p[0]))

static int xml_parse_textchar (char const *s, char const **ep, char *out) {
  if (s[0] != '&') {
    // int ch = scl_utf8_chsize (s[0]);
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

static char const *xml_parse_text (char const *s, char const **ep, char delim) {
  char const *p    = s;
  char       *tbuf = (char *)malloc (32);
  int         size = 32;
  int         i    = 0;
  memset (tbuf, 0, size);
  while (*p && *p != delim) {
    if (size - i >= 2)
      i += xml_parse_textchar (p, &p, tbuf + i);
    else {
      char *nbuf = (char *)malloc ((size_t)size + 256);
      memset (nbuf, 0, (size_t)size + 256);
      memcpy (nbuf, tbuf, size);
      free (tbuf);
      tbuf = nbuf;
      size += 256;
    }
  }
  (*ep) = p;
  if (*tbuf)
    return tbuf;
  return free (tbuf), NULL;
}

static xml_attr *xml_parse_attr (char const *s, char const **ep) {
  xml_attr    attr;
  char const *p = s;
  if (!mxissym (p))
    return NULL;
  memset (&attr, 0, sizeof (attr));
  s = p;
  while (mxissym (p))
    p++;
  attr.tag = scl_strncopy (s, p - s);
  if (p[0] != '=' && p[1] != '\"' && p[1] != '\'')
    return NULL;
  char delim = p[1];
  p += 2;
  s         = p;
  attr.data = xml_parse_text (s, &p, delim);
  p++;
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return ((*ep) = p), copy;
}

static xml_node *xml_parse_node (xml_doc *doc, xml_node *parent, char const *s,
  char const **ep) {
  static int  leave = 0;
  xml_node    node;
  char const *p = s;
  if (p[0] != '<')
    return NULL;
  memset (&node, 0, sizeof (xml_node));
  node.parent = parent;
  s           = ++p;
  if (mxissym (p)) {
    while (mxissym (p))
      p++;
    node.tag = scl_strncopy (s, p - s);
    s        = p;
    while (p[0] != '/' && p[0] != '>') {
      while ((unsigned char)*p <= 0x7f && isspace (p[0]))
        s = ++p;
      if (mxissym (p)) {
        xml_attr *attr = xml_parse_attr (s, &p);
        if (attr)
          xml_add_attr (&node, attr);
        else
          return xml_free_node (&node, XML_FREE_ONLY), NULL;
      }
    }
    if (*p == '/') {
      p += 2;
      return ((*ep) = p), memcpy (xml_page_slot (doc), &node, sizeof (node));

    } else if (*p == '>') {
      p++;
      if (mxissym (p) || isdigit (p[0]) || isspace (p[0])) {
        node.data = xml_parse_text (p, &p, '<');
      }
      while (*p == '<' || isspace (*p)) { // While there are child nodes
        s               = p;
        xml_node *cnode = xml_parse_node (doc, &node, p, &p);
        if (cnode && !leave)
          xml_add_child (&node, cnode);
        else if (leave)
          break;
        else if (!cnode)
          return xml_free_node (&node, XML_FREE_ONLY), NULL;
      }
    }
    if (leave) {
      p++;
      leave = 0;
      while (*p && isspace (*p)) {
        if (node._post && strlen (node._post) < 63) {
          ((char *)node._post)[strlen (node._post)] = *p;
          p++;
        } else {
          node._post = (char const *)malloc (64);
          memset ((void *)node._post, 0, 64);
        }
      }
      return ((*ep) = p), memcpy (xml_page_slot (doc), &node, sizeof (node));
    } else { // Is a parent, but ended before being terminated
      return xml_free_node (&node, XML_FREE_ONLY), NULL;
    }
  } else if (*p == '/') {
    if (parent) {
      p++;
      s = p;
      while (mxissym (p))
        p++;
      if (!strncmp (parent->tag, s, p - s))
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
        return p += 2, xml_parse_node (doc, NULL, p, ep);
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
  xml_page_add (&doc);
  xml_node *root = xml_parse_node (&doc, NULL, str, &p);
  if (!root)
    return NULL;
  memset (&doc, 0, sizeof (doc));
  doc.root      = root;
  xml_doc *copy = (xml_doc *)malloc (sizeof (doc));
  memcpy (copy, &doc, sizeof (doc));
  return copy;
}

xml_attr *xml_new_str_attr (char const *tag, char const *str) {
  if (!tag || !str)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag       = scl_strcopy (tag);
  attr.data      = scl_strcopy (str);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_new_int_attr (char const *tag, int i) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag       = scl_strcopy (tag);
  attr.data      = scl_fmt ("%i", i);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_new_float_attr (char const *tag, float n) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  attr.tag       = scl_strcopy (tag);
  attr.data      = scl_fmt ("%f", n);
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_node *xml_new_node (xml_doc *doc, char const *tag, char const *str) {
  if (!tag)
    return NULL;
  xml_node node;
  memset (&node, 0, sizeof (node));
  node.tag = scl_strcopy (tag);
  if (str) {
    node.data = scl_strcopy (str);
  }
  return memcpy (xml_page_slot (doc), &node, sizeof (node));
}

xml_node *xml_copy_node (xml_doc *doc, xml_node *node) {
  if (!doc || !node || !node->_page || !node->tag)
    return NULL;
  return memcpy (xml_page_slot (doc), node, sizeof (xml_node));
}

void xml_replace_node (xml_node *node, xml_node *with) {
  if (!node || !node->_page)
    return;
  if (with) {
    with->parent = node->parent;
    with->prev   = node->prev;
    with->next   = node->next;
    if (node->prev)
      node->prev->next = with;
    if (node->next)
      node->next->prev = with;
    xml_free_node (node, XML_FREE_ONLY);
  } else {
    xml_free_node (node, XML_FREE_PATCH);
  }
}

void xml_remove_attribute (xml_node *node, char const *tag) {
  if (!node || !node->_page || !node->attr)
    return;
}

xml_node **xml_xpath (xml_node *from, char const *path) {
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
  xml_node **paths = (xml_node **)malloc (sizeof (xml_node *) * size);
  memset (paths, 0, sizeof (xml_node *) * size);
  return paths;
}

static void xml_checkset (char **out, char **wp, int *size, int nlen) {
  int const astep = 32768;
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

#define xml_app_free(out, wp, size, str)  \
  {                                       \
    char *__text = (char *)str;           \
    int   __tlen = strlen (__text);       \
    xml_checkset (out, wp, size, __tlen); \
    memcpy (*wp, __text, __tlen);         \
    free ((void *)__text);                \
    *wp += __tlen;                        \
  }
#define xml_app(out, wp, size, str)       \
  {                                       \
    char *__text = (char *)str;           \
    int   __tlen = strlen (__text);       \
    xml_checkset (out, wp, size, __tlen); \
    memcpy (*wp, __text, __tlen);         \
    *wp += __tlen;                        \
  }
#define xml_napp(out, wp, size, str, max) \
  {                                       \
    char *__text = (char *)str;           \
    int   __tlen = max;                   \
    xml_checkset (out, wp, size, __tlen); \
    memcpy (*wp, __text, __tlen);         \
    *wp += __tlen;                        \
  }

static int xml_print_string (char const *str, char **out, char **wp, int *size,
  char keepquot) {
  char *p = (char *)str;
  for (; *p; p++) {
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
  if (!attr || !attr->tag || !attr->data)
    return 0;
  char        noapos    = scl_strffi (attr->data, "\'") == -1;
  char        noquot    = scl_strffi (attr->data, "\"") == -1;
  char        aposdelim = (noapos && !noquot) ? 1 : 0;
  char const *q         = !aposdelim ? "\"" : "\'";
  char const *q2        = !aposdelim ? "=\"" : "=\'";
  xml_napp (out, wp, size, " ", 1);
  xml_app (out, wp, size, attr->tag);
  xml_napp (out, wp, size, q2, 2);
  xml_print_string (attr->data, out, wp, size, aposdelim);
  xml_napp (out, wp, size, q, 1);
  return 1;
}

static int xml_print_node (xml_node *node, char **out, char **wp, int *size,
  char isroot) {
  if (!node)
    return 0;
  xml_node *inode = node;
  for (; inode && inode->tag; inode = inode->next) {
    xml_app (out, wp, size, scl_fmt ("<%s", inode->tag));
    if (inode->attr) {
      xml_attr *attr = inode->attr;
      for (; attr; attr = attr->next)
        xml_print_attr (attr, out, wp, size);
    }
    if (inode->child || isroot || inode->data) {
      xml_napp (out, wp, size, ">", 1);
      if (inode->data)
        xml_print_string (inode->data, out, wp, size, 0);
      xml_print_node (inode->child, out, wp, size, 0);
      xml_app (out, wp, size, scl_fmt_static ("</%s>", inode->tag));
    } else {
      xml_napp (out, wp, size, "/>", 2);
    }
    if (inode->_post)
      xml_app (out, wp, size, inode->_post);
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
  xml_print_node (doc->root, &out, &wp, &size, 1);
  return out;
}
