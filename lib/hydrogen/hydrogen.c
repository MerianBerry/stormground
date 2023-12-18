/*
MIT License

Copyright (c) 2023 Kody Stanley

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See github at https:/*github.com/MerianBerry/hydrogen
*/

/*
  hydrogen.c
  Hydrogen source file
*/

#define _XOPEN_SOURCE 700
#define HYDROGEN_ALL
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _WIN32
#  include <windows.h>
#else
/* #  include <dirent.h> */
#  include <unistd.h>
#endif

#include "hydrogen.h"

#if !defined(MAX)
#  define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
#if !defined(MIN)
#  define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif
#if !defined(CLAMP)
#  define CLAMP(x, y, z) MAX (y, MIN (z, x))
#endif

#pragma region "TIME"

h_timepoint timenow() {
#if defined(_WIN32)
  h_timepoint   tp;
  LARGE_INTEGER pc;
  QueryPerformanceCounter (&pc);
  tp.c = pc.QuadPart;
  return tp;
#elif defined(__GNUC__)
  timespec_t ts;
  timespec_get (&ts, 1);
  h_timepoint tp;
  tp.s  = ts.tv_sec;
  tp.ns = ts.tv_nsec;
  return tp;
#endif
}

void microsleep (long usec) {
#ifdef __unix__
  usleep (usec);
#elif defined(_WIN32)
  HANDLE        timer;
  LARGE_INTEGER ft;

  ft.QuadPart = -(10 * usec); /* Convert to 100 nanosecond interval, negative */
  /* value indicates relative time */

  timer = CreateWaitableTimer (NULL, TRUE, NULL);
  SetWaitableTimer (timer, &ft, 0, NULL, NULL, 0);
  WaitForSingleObject (timer, INFINITE);
  CloseHandle (timer);
#endif
}

double timeduration (h_timepoint end, h_timepoint start, double ratio) {
#if defined(_WIN32)
  LARGE_INTEGER pf;
  QueryPerformanceFrequency (&pf);
  double ndif = (double)(end.c - start.c) / (double)pf.QuadPart;
  return ndif * ratio;
#elif defined(__GNUC__)
  double t1 = (double)end.s + (double)end.ns / 1000000000.0;
  double t2 = (double)start.s + (double)start.ns / 1000000000.0;

  return (t1 - t2) * ratio;
#endif
}

#if defined(_WIN32)
/* Windows sleep in 100ns units */
BOOLEAN _nanosleep (LONGLONG ns) {
  /* Declarations */
  HANDLE        timer; /* Timer handle */
  LARGE_INTEGER li; /* Time defintion */
  /* Create timer */
  if (!(timer = CreateWaitableTimer (NULL, TRUE, NULL)))
    return FALSE;
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

void wait (double seconds) {
#ifdef __unix__
  h_timepoint s = timenow();
  timespec_t  ts, tsr = {2000, 0};
  while (timeduration (timenow(), s, seconds_e) < seconds) {
    nanosleep (&ts, &tsr);
  }
#elif defined(_WIN32)
  h_timepoint s = timenow();
  while (timeduration (timenow(), s, seconds_e) < seconds) {
    _nanosleep (10);
  }
#endif
}

void waitms (double ms) {
#ifdef __unix__
  h_timepoint s  = timenow();
  timespec_t  ts = {2000, 0};
  ts.tv_sec      = ms / 1000.0;
  ts.tv_nsec     = fmodf (ms, 1000) * 1000000.0;
  while (nanosleep (&ts, &ts) == -1)
    ;
#elif defined(_WIN32)
  LONGLONG ns = ms * 1000 * 10;
  /* printf("%li\n", ns); */
  _nanosleep (ns);
#endif
}

#pragma endregion "TIME"

#pragma region "STRING"

char *str_add (char *lhs, char const *rhs) {
  if (!rhs)
    return NULL;
  size_t lhss = 0;
  if (!!lhs)
    lhss = strlen (lhs);

  size_t size = lhss + strlen (rhs) + 1;
  char  *buf  = (char *)malloc (size);
  memset (buf, 0, size);
  if (!!lhs)
    memcpy (buf, lhs, lhss);
  memcpy (buf + lhss, rhs, strlen (rhs));

  return buf;
}

char *str_substr (char const *src, size_t off, size_t len) {
  assert (!(off > strlen (src) - 1) && "String out of bounds exception");

  size_t size = MIN (strlen (src) - off, len) + 1;
  char  *buf  = (char *)malloc (size);
  memset (buf, 0, size);
  memcpy (buf, src + off, size - 1);
  return buf;
}

size_t str_ffo (char const *str, char c) {
  size_t i;
  for (i = 0; i < strlen (str); ++i) {
    if (str[i] == c)
      return i;
  }
  return npos;
}

size_t str_flo (char const *str, char c) {
  long i;
  for (i = strlen (str) - 1; i >= 0; --i) {
    if (str[i] == c)
      return i;
  }
  return npos;
}

size_t str_flox (char const *str, char const *cs) {
  long   i1;
  size_t i2;
  for (i1 = strlen (str) - 1; i1 >= 0; --i1) {
    for (i2 = 0; i2 < strlen (cs); ++i2) {
      char c = cs[i2];
      if (str[i1] == c)
        return i1;
    }
  }
  return npos;
}

size_t str_ffi (char const *str, char const *cmp) {
  if (!str || !cmp) {
    return npos;
  }
  size_t     i;
  long const l1 = strlen (str);
  long const l2 = strlen (cmp);
  if (!l1 || !l2)
    return npos;
  for (i = 0; i < l1 - (l2 - 1); ++i) {
    char *sub = (char *)str_substr (str, i, l2);
    if (!strcmp (sub, cmp)) {
      free (sub);
      return i;
    }
    free (sub);
  }
  return npos;
}

size_t str_fli (char const *str, char const *cmp) {
  if (!strlen (cmp))
    return npos;
  long         i;
  const size_t s1 = strlen (str);
  const size_t s2 = strlen (cmp);
  if (s2 > s1)
    return npos;
  for (i = s1 - (s2); i >= 0; --i) {
    char *sub = (char *)str_substr (str, i, s2);
    if (!strcmp (sub, cmp)) {
      free (sub);
      return i;
    }
    free (sub);
  }
  return npos;
}

unsigned long str_hash (char const *str) {
  unsigned long hash = 5381;
  int           c;

  while (c = *(str++)) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

#ifndef va_copy
#  define va_copy __builtin_va_copy
#endif

/* Str fmting based off of lua fmt function */
char *str_fmtv (char const *fmt, va_list args) {
  va_list copy;
  va_copy (copy, args);
  int size = vsnprintf (NULL, 0, fmt, copy) + 1;
  va_end (copy);
  char *str = malloc (size);
  vsnprintf (str, size, fmt, args);
  return str;
}

char *str_fmt (char const *fmt, ...) {
  char   *msg;
  va_list args;
  va_start (args, fmt);
  msg = (char *)str_fmtv (fmt, args);
  va_end (args);
  return msg;
}

char const *str_cpy (char const *src, size_t bytes) {
  size_t len = MIN (strlen (src), bytes);
  char  *cpy = malloc (len + 1);
  memset (cpy, 0, len + 1);
  memcpy (cpy, src, len);
  return cpy;
}

char *str_append (char *src, char const *nstr, size_t bytes) {
  if (!nstr || !strlen (nstr) || !bytes)
    return src;
  const size_t l   = src ? strlen (src) : 0;
  const size_t l2  = MIN (strlen (nstr), bytes);
  char        *buf = malloc (l + l2 + 1);
  memset (buf, 0, l + l2 + 1);
  if (src) {
    memcpy (buf, src, l);
  }
  memcpy (((char *)buf) + l, nstr, l2);
  return buf;
}

char *str_replace (char const *src, long off, long len, char const *str) {
  if (!src || !str)
    return NULL;
  off           = MAX (off, 0);
  len           = MAX (len, 0);
  long const l1 = strlen (src);
  long const l2 = strlen (str);
  if (off >= l1)
    return NULL;
  len             = MIN (len, l1 - off);
  long const l3   = l1 - len + l2;
  char      *nstr = malloc (l3 + 1);
  memset (nstr, 0, l3 + 1);
  memcpy (nstr, src, MAX (off, 0));
  memcpy (nstr + off, str, MAX (l2, 0));
  memcpy (nstr + off + l2, src + off + len, MAX (l1 - off - len, 0));
  return nstr;
}

char *str_colorfmtv (char const *src, va_list args) {
  char *cpy = str_fmtv (src, args);
  int   itr = 0;
  while (1) {
    if (itr > 100) {
      printf (
          "\x1B[91;1mEmergency while loop abort at itr=%i\n\tstring: "
          "\"%s\"\n\x1B[0m",
          itr, cpy);
      break;
    }
    size_t p = str_ffi (cpy, "&c");
    if (p == npos)
      break;
    if (((p > 0 && cpy[p - 1] != '\\') || !p) && cpy[p + 2] == '(') {
      size_t eb    = str_ffo (cpy + p, ')') + p;
      char  *color = (char *)str_substr (cpy, p + 3, eb - (p + 3));
      if (color) {
        char *ocolor = NULL;
        switch (str_hash (color)) {
        case 210707760194U: ocolor = "\x1B[30m"; break;
        case 14928609233751675713U: ocolor = "\x1B[90m"; break;
        case 193504576U: ocolor = "\x1B[31m"; break;
        case 8246139787930773631U: ocolor = "\x1B[91m"; break;
        case 210713909846U: ocolor = "\x1B[32m"; break;
        case 14928609233757825365U: ocolor = "\x1B[92m"; break;
        case 6954248304353U: ocolor = "\x1B[33m"; break;
        case 13028758798249174464U: ocolor = "\x1B[93m"; break;
        case 6385084301U: ocolor = "\x1B[34m"; break;
        case 13868195969781240492U: ocolor = "\x1B[94m"; break;
        case 229474533704194U: ocolor = "\x1B[35m"; break;
        case 5673926631242730689U: ocolor = "\x1B[95m"; break;
        case 6385133744U: ocolor = "\x1B[36m"; break;
        case 13868195969781289935U: ocolor = "\x1B[96m"; break;
        case 210726503048: ocolor = "\x1B[0m"; break;
        }
        if (!ocolor) {
          printf ("\x1B[91mInvalid color name used. %s\n\x1B[0m", color);
          ocolor = "";
        }
        free (color);
        cpy = str_replace (cpy, p, eb - p + 1, ocolor);
      }
    }
    ++itr;
  }
  return cpy;
}

char *str_colorfmt (char const *src, ...) {
  va_list args;
  va_start (args, src);
  char *str = str_colorfmtv (src, args);
  va_end (args);
  return str;
}

int utf8_charsize (uint8_t c) {
  if (c >= 0xf0 && c <= 0xf4)
    return 4;
  else if (c >= 0xe0)
    return 3;
  else if (c >= 0xc2)
    return 2;
  return 1;
}

long utf8_strlen (char const *str) {
  if (!str)
    return -1;
  long s = 0;
  long i;
  for (i = 0; i < STR_MAX; ++s) {
    if (!str[i])
      break;
    int us = utf8_charsize (((uint8_t *)str)[i]);
    i += us;
  }
  return s;
}

long utf8_actual (char const *str, long off) {
  if (!str)
    return -1;
  long const l1 = utf8_strlen (str);
  off           = mini (l1 - 1, off);
  long s        = 0;
  long i;
  for (i = 0; i < off; ++i) {
    s += utf8_charsize (str[s]);
  }
  return s;
}

int utf8_encode (int utf) {
  int out = 0;
  /* 4 byte */
  if (utf > 0xffff) {
    uint8_t one = 30 << 3 | utf >> 18 & 0x7;
    uint8_t two = 2 << 6 | utf >> 12 & 0x3f;
    uint8_t tre = 2 << 6 | utf >> 6 & 0x3f;
    uint8_t qua = 2 << 6 | utf & 0x3f;
    out         = one | two << 8 | tre << 16 | qua << 24;
  } /* 3 byte */
  else if (utf > 0x7ff) {
    uint8_t one = 14 << 4 | utf >> 12 & 0xf;
    uint8_t two = 2 << 6 | utf >> 6 & 0x3f;
    uint8_t tre = 2 << 6 | utf & 0x3f;
    out         = one | two << 8 | tre << 16;
  } /* 2 byte */
  else if (utf > 0x7f) {
    uint8_t one = 6 << 5 | utf >> 6 & 0x1f;
    uint8_t two = 2 << 6 | utf & 0x3f;
    out         = one | two << 8;
  } /* 1 byte */
  else {
    return utf;
  }
  return out;
}

int utf8_decode (int utf8) {
  int out = 0;
  /* Is ASCII? */
  if (!utf8 >> 7)
    return utf8;
  int c = utf8_charsize (*(uint8_t *)&utf8);
  int i;
  for (i = c - 1; i >= 1; --i) {
    out |= (utf8 >> i * 8 & 0x3f) << ((i - 1) * 6);
  }
  out |= (utf8 & (powi (2, 8 - c - 1) - 1)) << (c - 1) * 6;
  return out;
}

int utf8_swap (int utf8) {
  int out = (utf8 & 0xff) << 24 | (utf8 >> 8 & 0xff) << 16 |
            (utf8 >> 16 & 0xff) << 8 | (utf8 >> 24 & 0xff);
}

int utf8_literal (int utf) {
#if 1
  int out = 0;
  int _i  = 0;
  int i;
  for (i = sizeof (int) - 1; i >= 0; --i) {
    uint8_t c = utf >> i * 8 & 0xff;
    if (c) {
      out |= c << _i * 8;
      ++_i;
    }
  }
  return out;
#else
  int o = utf8_swap (utf);
  while (!(o & 0xff)) {
    o >>= 8;
  }
  return o;
#endif
}

char *utf8_tostring (int utf8) {
  int   l   = utf8_charsize (*(uint8_t *)&utf8);
  char *str = malloc (l + 1);
  memset (str, 0, l + 1);
  memcpy (str, &utf8, l);
  return str;
}

int errorfv (char const *fmt, va_list args) {
  int r = 1;
#if defined(__unix__)
  char *str  = str_append ("&c(bright_red)", fmt, npos);
  char *str2 = str_append (str, "&c(reset)", npos);
  free (str);
  str = str_colorfmtv (str2, args);
  free ((void *)str2);
#elif defined(_WIN32)
  char *str   = (char *)str_fmtv (fmt, args);
#endif
  if (!str) {
    r = 0;
    goto errorfEnd;
  }
  fprintf (stderr, "%s", str);
  free ((void *)str);
errorfEnd:
  return r;
}

int errorf (char const *fmt, ...) {
  va_list args;
  va_start (args, fmt);
  int r = errorfv (fmt, args);
  va_end (args);
  return r;
}

int warningfv (char const *fmt, va_list args) {
  int   r    = 1;
  char *str  = str_append ("&c(yellow)", fmt, npos);
  char *str2 = str_append (str, "&c(reset)", npos);
  free (str);
  str = str_colorfmtv (str2, args);
  free ((void *)str2);
  if (!str) {
    r = 0;
    goto warningfEnd;
  }
  fprintf (stderr, "%s", str);
  free ((void *)str);
warningfEnd:
  return r;
}

int warningf (char const *fmt, ...) {
  va_list args;
  va_start (args, fmt);
  int r = warningfv (fmt, args);
  va_end (args);
  return r;
}

#pragma endregion "STRING"

#pragma region "AVL"

int avl_height (avl_node_t *base) {
  if (!base) /* If base is NULL, return no height */
    return 0;
  int count = 1;

  int left  = 0;
  int right = 0;
  /* Find left */
  if (!!base->left) {
    left = avl_height (base->left);
  }
  /* Find right */
  if (!!base->right) {
    right = avl_height (base->right);
  }
  count += MAX (left, right);
  return count;
}

int avl_findbalance (avl_node_t *base) {
  int balance = 0;

  if (!base)
    return 0;
  balance += avl_height (base->right);
  balance -= avl_height (base->left);

  return balance;
}

avl_node_t **avl_fside (avl_node_t *parent, avl_node_t *target) {
  if (parent->left == target)
    return &parent->left;
  else if (parent->right == target)
    return &parent->right;
  return NULL;
}

void avl_leftrot (avl_node_t *X, avl_node_t *Z) {
  avl_node_t *DC = Z->left;
  if (DC)
    DC->parent = X;
  X->right  = DC;
  Z->parent = X->parent;
  Z->left   = X;
  if (X->parent)
    *avl_fside (X->parent, X) = Z;
  X->parent = Z;
}

void avl_rightrot (avl_node_t *X, avl_node_t *Z) {
  avl_node_t *DC = Z->right;
  if (DC)
    DC->parent = X;
  X->left   = DC;
  Z->parent = X->parent;
  Z->right  = X;
  if (X->parent)
    *avl_fside (X->parent, X) = Z;
  X->parent = Z;
}

void avl_balance (avl_tree_t *bintree, avl_node_t *base) {
  avl_node_t *X          = base->parent;
  char        rootswitch = X == bintree->root;
  while (X) {
    rootswitch  = X == bintree->root;
    int balance = avl_findbalance (X);
    if (balance <= -2) /* Left child */
    {
      avl_node_t *Z    = X->left;
      int         bal2 = avl_findbalance (Z);
      if (bal2 <= 0) /* Right rotation */
      {
        avl_rightrot (X, Z);
      } else /* Left Right rotation */
      {
        avl_node_t *Y = Z->right;
        avl_leftrot (Z, Y);
        avl_rightrot (X, Y);
      }
      break;
    } else if (balance >= 2) {
      avl_node_t *Z    = X->right;
      int         bal2 = avl_findbalance (Z);
      if (bal2 > 0) /* Left rotation */
      {
        avl_leftrot (X, Z);
      } else /* Right Left rotation */
      {
        avl_node_t *Y = Z->left;
        avl_rightrot (Z, Y);
        avl_leftrot (X, Y);
      }
      break;
    }
    if (X == X->parent)
      break;
    X = X->parent;
  }
  if (rootswitch && X)
    bintree->root = X->parent;
  if (!!bintree->root->parent)
    bintree->root = bintree->root->parent;
}

void avl_create (avl_tree_t *bintree, avl_node_t **target, avl_node_t *parent,
                 char const *key, void *mem) {
  *target = (avl_node_t *)malloc (sizeof (avl_node_t));
  memset (*target, 0, sizeof (avl_node_t));

  (*target)->mem = mem;

  int keysize    = strlen (key) + 1;
  (*target)->key = (char *)malloc (keysize);
  memset ((*target)->key, 0, keysize);
  memcpy ((*target)->key, key, keysize - 1);

  (*target)->parent = parent;
  bintree->size += 1;
  avl_balance (bintree, *target);
}

avl_node_t *avl_find (avl_tree_t *bintree, char const *key) {
  if (!bintree)
    return NULL;
  avl_node_t *itr = bintree->root;
  while (!!itr && !!itr->key) {
    int cmp = strcmp (itr->key, key);
    if (cmp == 0) {
      return itr;
    } else if (cmp < 0) {
      if (!!itr->left) {
        itr = itr->left;
        continue;
      }
    } else /* cmp is > 0 */
    {
      if (!!itr->right) {
        itr = itr->right;
        continue;
      }
    }
    break;
  }
  return NULL;
}

void avl_append (avl_tree_t *bintree, char const *key, void *mem) {
  if (!bintree->root) {
    avl_create (bintree, &bintree->root, NULL, key, mem);
    return;
  }
  avl_node_t *itr  = bintree->root;
  int         _itr = 0;
  while (!!itr) {
    if (_itr > 1000)
      return;
    _itr += 1;
    int cmp = strcmp (itr->key, key);
    if (cmp == 0) {
      itr->mem = mem;
      return;
    } else if (cmp < 0) {
      if (!!itr->left) {
        itr = itr->left;
        continue;
      }
      avl_create (bintree, &itr->left, itr, key, mem);
      return;
    } else /* cmp is > 0 */
    {
      if (!!itr->right) {
        itr = itr->right;
        continue;
      }
      avl_create (bintree, &itr->right, itr, key, mem);
      return;
    }
  }
}

void avl_destroysubtree (avl_tree_t *tree, avl_node_t *root) {
  if (!root)
    return;
  free (root->key);
  avl_destroysubtree (tree, root->left);
  avl_destroysubtree (tree, root->right);
  if (tree->size > 0)
    --tree->size;
  free (root);
}

void avl_relocate (avl_tree_t *tree, avl_node_t *root) {
  if (!root)
    return;
  root->parent = NULL;
  avl_append (tree, root->key, root->mem);
  --tree->size;
  avl_relocate (tree, root->left);
  avl_relocate (tree, root->right);
  free (root->key);
  free (root);
}

void avl_destroynode (avl_tree_t *tree, avl_node_t *node) {
  if (!node)
    return;
  avl_node_t **n = NULL;
  if (node->parent)
    n = avl_fside (node->parent, node);
  else
    tree->root = NULL;
  if (n)
    (*n) = NULL;
  avl_relocate (tree, node->left);
  avl_relocate (tree, node->right);
  free (node->key);
  free (node);
  --tree->size;
  if (!tree->size)
    tree->root = NULL;
}

void avl_clear (avl_tree_t *bintree) {
  avl_destroysubtree (bintree, bintree->root);
  bintree->root = NULL;
  bintree->size = 0;
}

void avl_free (avl_tree_t **bintree) {
  avl_destroysubtree (*bintree, (*bintree)->root);
  (*bintree)->root = NULL;
  (*bintree)->size = 0;
  free ((*bintree));
  *bintree = NULL;
}

void avl_freeX (avl_tree_t *bintree) {
  avl_destroysubtree (bintree, bintree->root);
  bintree->root = NULL;
  bintree->size = 0;
  free (bintree);
}

avl_tree_t *avl_newtree() {
  avl_tree_t *ptr = (avl_tree_t *)malloc (sizeof (avl_tree_t));
  return ptr;
}

#pragma endregion "AVL"

#pragma region "IO"
#ifdef UNDEP_DIRENT
#  ifdef USE_DIRENT
int io_scandir (char const *dir, dirent_t ***pList, int *pCount) {
  DIR *d;
  int  count = scandir (dir, pList, NULL, NULL);
  if (count < 0)
    return 0;
  (*pCount) = count;
  return 1;
}

#  endif
#endif

#ifdef _WIN32
#  include <winbase.h>
#elif defined(__unix__)
#  include <dirent.h>
#endif

typedef struct stat stat_t;
typedef char       *dirToken;

dirToken *io_parseDirectory (char const *path, int *count) {
  int          i;
  const size_t l = strlen (path);

  dirToken *tokens = NULL;

  int c = 0;
  for (i = 0; i < l; ++i) {
    size_t   p = MIN (str_ffo (path + i, '\\'), str_ffo (path + i, '/'));
    dirToken t = (dirToken)str_substr (path, i, p);
    tokens     = mem_grow (tokens, sizeof (dirToken), c, &t, 1);
    ++c;
    if (p == npos)
      break;
    i += p;
  }
}

/*char *io_fullpath (char const *path) {
  int       i;
  char     *fpath  = NULL;
  int       c      = 0;
  dirToken *tokens = NULL;
  if (!path)
    return NULL;
  if (path[0] == '~' || path[0] == '/') {}

  io_parseDirectory (path, &c);
#if defined(_WIN32)
  char  var[PATH_MAX + 1] = {0};
  DWORD l                 = GetEnvironmentVariable ("HOMEDRIVE", var, PATH_MAX);
  GetEnvironmentVariable ("HOMEPATH", var + l, PATH_MAX - l);
#elif defined(__unix__)
  char *var   = getenv ("HOME");
#endif
  fpath = str_append (var, "/", npos);
  if (!strcmp (tokens[0], "~")) {
    free ((void *)tokens[0]);
    tokens = &tokens[1];
    --c;
  }
  for (i = 0; i < c; ++i) {
    if (!strcmp (tokens[i], "~")) {
      free ((void *)fpath);
      fpath = NULL;
      goto cleanup;
    }
  }
  for (i = 0; i < c; ++i) {
    printf ("dir token: %s\n", tokens[i]);
    if (!strcmp (tokens[i], "..")) {}
  }
cleanup:
  for (i = 0; i < c; ++i) {
    free ((void *)tokens[i]);
  }
  free ((void *)tokens);
  return NULL;
}*/

char *io_fixhome (char const *path) {
#if defined(_WIN32)
  char  var[PATH_MAX + 1] = {0};
  DWORD l                 = GetEnvironmentVariable ("HOMEDRIVE", var, PATH_MAX);
  GetEnvironmentVariable ("HOMEPATH", var + l, PATH_MAX - l);
#else
  char *var   = getenv ("HOME");
#endif
  long pos = str_ffo (path, '~');
  if (pos != npos && var) {
    char *nstr = str_replace (path, pos, 1, var);
    return nstr;
  }
  return (char *)str_cpy (path, strlen (path));
}

/*
char io_direxists (char const *path) {
  char *npath = io_fixhome (path);
  DIR  *d     = opendir (npath);
  free (npath);
  if (!d)
    return 0;
  closedir (d);
  return 1;
}
*/

char io_exists (char const *path) {
  char *npath = io_fixhome (path);
  FILE *f     = fopen (npath, "r");
  free (npath);
  if (!f)
    return 0;
  fclose (f);
  return 1;
}

void io_mkdir (char const *path) {
#ifdef __unix__
  stat_t s     = {0};
  char  *npath = io_fixhome (path);
  if (stat (npath, &s) == -1) {
    mkdir (npath, 0755);
  }
  free (npath);
#elif _WIN32
  char *npath = io_fixhome (path);
  CreateDirectoryA (npath, NULL);
  free (npath);
#endif
}

h_buffer io_read (char const *path) {
  if (!path)
    return (h_buffer){NULL, 0};
  size_t i;
  char  *fp     = io_fixhome (path);
  FILE  *stream = fopen (fp, "r");
  if (!stream) {
    free (fp);
    return (h_buffer){NULL, 0};
  }
  fseek (stream, -1, SEEK_END);
  long     strlen = ftell (stream) + 1;
  h_buffer buf    = {0};
  buf.data        = malloc (strlen);
  buf.size        = strlen;
  fseek (stream, 0, SEEK_SET);
  for (i = 0; i < (size_t)strlen; ++i) {
    ((char *)buf.data)[i] = getc (stream);
  }
  free (fp);
  fclose (stream);
  return buf;
}

#pragma endregion "IO"

#pragma region "MEM"

void *mem_grow (void *src, int stride, int len, void *newData, int newDataLen) {
  void *buf = malloc (stride * (len + newDataLen));
  memset (buf, 0, stride * (len + newDataLen));
  memcpy (buf, src, stride * len);
  memcpy ((char *)buf + stride * len, newData, stride * newDataLen);
  if (src)
    free (src);
  return buf;
}

void *mem_copy (void *src, int size) {
  void *pb = malloc (size);
  memcpy (pb, src, size);
  return pb;
}

#pragma endregion "MEM"

#pragma region "VECTOR"

float const pi = 3.14159f;

float distance2d (h_vec2 v) { return sqrtf (v.x * v.x + v.y * v.y); }

float distance3d (h_vec3 v) {
  return sqrtf (v.x * v.x + v.y * v.y + v.z * v.z);
}

float dir2d (h_vec2 v) {
  if (!v.y && v.x > 0.f)
    return 0.f;
  else if (!v.y && v.x < 0.f)
    return pi;
  else if (!v.x && v.y > 0.f)
    return pi / 2.f;
  else if (!v.x && v.y < 0.f)
    return 3.f * pi / 2.f;
  else if (!v.x && !v.y)
    return 0.f;
  float theta = atanf (v.y / v.x);
  if (v.x < 0.f)
    theta = pi + theta;
  return theta;
}

h_vec2 plus2d (h_vec2 a, h_vec2 b) { return (h_vec2){a.x + b.x, a.y + b.y}; }

h_vec2 sub2d (h_vec2 a, h_vec2 b) { return (h_vec2){a.x - b.x, a.y - b.y}; }

h_vec2 mag2d (h_vec2 v, float m) { return (h_vec2){v.x * m, v.y * m}; }

h_vec2 normalize2d (h_vec2 v) {
  float mag = distance2d (v);
  return (h_vec2){v.x / mag, v.y / mag};
}

h_vec3 normalize3d (h_vec3 v) {
  float mag = distance3d (v);
  return (h_vec3){v.x / mag, v.y / mag, v.z / mag};
}

float dot2d (h_vec2 a, h_vec2 b) { return a.x * b.x + a.y * b.y; }

float dot3d (h_vec3 a, h_vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

#pragma endregion "VECTOR"

#pragma region "MATH"

int powi (int x, int y) {
  int o = x;
  int i;
  for (i = 0; i < y - 1; ++i) o *= x;
  return o;
}

double minf (double x, double y) { return (x < y) ? x : y; }

double maxf (double x, double y) { return (x > y) ? x : y; }

float clampf (float x, float y, float z) {
  return (x < y) ? y : ((x > z) ? z : x);
}

int mini (int x, int y) { return (x < y) ? x : y; }

int maxi (int x, int y) { return (x > y) ? x : y; }

int clampi (int x, int y, int z) { return (x < y) ? y : ((x > z) ? z : x); }

#pragma endregion "MATH"