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

#ifndef PATH_MAX
#  define PATH_MAX MAX_PATH
#endif

static void scl_pageset (scl_page *page, unsigned size) {
  page->next_ = NULL;
  page->data  = malloc (size);
  page->size  = size;
  page->used  = 0;
}

scl_page *scl_pagenew (unsigned size) {
  scl_page *page = malloc (sizeof (scl_page));
  page->next_    = NULL;
  page->data     = malloc (size);
  page->size     = size;
  page->used     = 0;
  return page;
}

void *scl_pagealloc (scl_page *page, unsigned size) {
  if (!page->data) {
    unsigned req = size > SCL_DEFAULT_PAGE_SIZE ? size : SCL_DEFAULT_PAGE_SIZE;
    page->data   = malloc (req);
    memset (page->data, 0, req);
    page->size = req;
  }
  if (page->used + size > page->size) {
    /* make a new page, and swap input page for new one */
    /* saves performance and cpu time looking of open slot */
    unsigned  req = size > SCL_DEFAULT_PAGE_SIZE ? size : SCL_DEFAULT_PAGE_SIZE;
    scl_page *npage = scl_pagenew (req);
    scl_page  tmp   = *npage;
    *npage          = *page;
    *page           = tmp;
    page->next_     = npage;
    return scl_pagealloc (page, size);
  }
  void *ptr = (char *)page->data + page->used;
  page->used += size;
  return ptr;
}

void scl_freepages (scl_page *page) {
  if (page->data)
    free ((void *)page->data);
  // Dont free the first page
  page = page->next_;
  for (; page;) {
    scl_page *next = page->next_;
    if (page->data)
      free ((void *)page->data);
    free (page);
    page = next;
  }
}

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

#ifdef _WIN32
static LARGE_INTEGER base_clock = {.QuadPart = 0};
#endif

void scl_resetclock() {
#ifdef _WIN32
  QueryPerformanceCounter (&base_clock);
#endif
}

double scl_clock() {
#if defined(_WIN32)
  LARGE_INTEGER pc;
  LARGE_INTEGER pf;
  QueryPerformanceCounter (&pc);
  QueryPerformanceFrequency (&pf);
  return (double)(pc.QuadPart - base_clock.QuadPart) / (double)pf.QuadPart;
#elif defined(__unix__)
  timespec_t ts;
  timespec_get (&ts, 1);
  return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
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

unsigned scl_fsize (scl_file *F) {
  if (!F || !F->stream)
    return 0;
  unsigned off = ftell ((FILE *)F->stream);
  fseek ((FILE *)F->stream, 0, SEEK_END);
  unsigned len = ftell ((FILE *)F->stream);
  fseek ((FILE *)F->stream, off, SEEK_SET);
  return len;
}

unsigned scl_read (scl_file *F, void *buffer, unsigned const n) {
  if (!F)
    return 0;
  unsigned size = scl_fsize (F);
  if (!buffer)
    return size;
  return fread (buffer, 1, size < n ? size : n, (FILE *)F->stream);
}

unsigned scl_read_malloc (scl_file *F, void **buffer, unsigned const n) {
  if (!buffer)
    return 0;
  unsigned size = scl_fsize (F);
  char    *buf  = (char *)malloc ((size_t)size + 1);
  memset (buf, 0, (size_t)size + 1);
  (*buffer) = buf;
  return scl_read (F, buf, n);
}

int scl_write (scl_file *F, void const *buffer, int const n) {
  if (!F || !F->stream || !buffer || n < 0)
    return -1;
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
  static char fpath[PATH_MAX];
#if defined(_WIN32)
  _fullpath (fpath, rel, PATH_MAX);
#elif defined(__unix__)
  realpath (path, fpath);
#endif
  char *copy = malloc (PATH_MAX);
  memcpy (copy, fpath, PATH_MAX);
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

char const *scl_filename (char const *path) {
  if (!path)
    return NULL;
  char const *abs = scl_realpath (path);
  path            = abs;
  int   l         = strlen (path);
  char *p         = (char *)path + l - 1;
  int   n         = -1;
  for (; *p && p >= path; --p)
    if (*p == '/' || *p == '\\') {
      p++;
      break;
    }
  n               = p - path;
  char const *out = p != path ? scl_strncopy (p, n) : scl_strcopy (".");
  free ((void *)path);
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
  char buf[PATH_MAX + 1];
  memset (buf, 0, sizeof (buf));
  GetModuleFileName (NULL, buf, PATH_MAX);
#else
  char    buf[PATH_MAX];
  ssize_t count = readlink ("/proc/self/exe", buf, PATH_MAX);
#endif
  return scl_parentpath (buf);
}

#define scl_checkScanR(buf, dsect, n, m)                          \
  if (n > m) {                                                    \
    m              = n + 3;                                       \
    char **nbuf_   = malloc (sizeof (char *) * m + PATH_MAX * m); \
    char  *ndsect_ = (char *)nbuf_ + sizeof (char *) * m;         \
    memset (nbuf_, 0, sizeof (char *) * m + PATH_MAX * m);        \
    if (buf) {                                                    \
      memcpy (ndsect_, dsect, PATH_MAX *n);                       \
      free ((void *)buf);                                         \
    }                                                             \
    int i_ = 0;                                                   \
    for (; i_ < m; i_++) {                                        \
      nbuf_[i_] = ndsect_ + PATH_MAX * i_;                        \
    }                                                             \
    dsect = ndsect_;                                              \
    buf   = nbuf_;                                                \
  }

#define scl_addScanRI(buf, dsect, n, m, I)                    \
  {                                                           \
    n++;                                                      \
    scl_checkScanR (buf, dsect, n, m);                        \
    if (strlen (I) < PATH_MAX)                                \
      memcpy (dsect + PATH_MAX * (n - 1), I, strlen (I) + 1); \
  }

static int scl_scanDir_ (char const *dir, char const *mask, char ***buf_,
  char **dsect_, int *n_, int *m_) {
  char **buf   = *buf_;
  char  *dsect = *dsect_;
  int    n     = *n_;
  int    m     = *m_;

#ifdef _WIN32
  HANDLE           hFind = NULL;
  WIN32_FIND_DATAA ffd;
  char const      *spec = scl_fmt_static ("%s\\%s", dir, mask);
  hFind                 = FindFirstFileA (spec, &ffd);
  if (hFind == NULL)
    return 1;
  do {
    if (!!strcmp (ffd.cFileName, ".") && !!strcmp (ffd.cFileName, "..")) {
      char const *I = scl_fmt ("%s\\%s", dir, ffd.cFileName);
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        scl_scanDir_ (I, mask, &buf, &dsect, &n, &m);
      } else {
        scl_addScanRI (buf, dsect, n, m, I);
      }
      free ((void *)I);
    }
  } while (FindNextFile (hFind, &ffd) != 0);
  FindClose (hFind);
#endif
  (*buf_)   = buf;
  (*dsect_) = dsect;
  (*n_)     = n;
  (*m_)     = m;
  return 0;
}

char const **scl_scanDir (char const *dir, char const *mask, int *count) {
  char **buf   = NULL;
  char  *dsect = NULL;
  int    n     = 0;
  int    m     = -1;

  // char const *abs = scl_realpath (dir);
  scl_scanDir_ (dir, mask, &buf, &dsect, &n, &m);
  // free ((void *)abs);

  (*count) = n;
  return (char const **)buf;
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
  return scl_strncat (str,
    str2,
    strlen (str ? str : ""),
    strlen (str2 ? str2 : ""),
    freestr);
}

char const *scl_strncat2 (char *str, char const *str2, int n, int n2) {
  if (!str)
    return NULL;
  n  = n >= 0 ? n : 0;
  n2 = n2 >= 0 ? n2 : 0;
  if (str2 && n2)
    memcpy (str + n, str2, n2);
  str[n + n2] = 0;
  return str + n + n2;
}

char const *scl_strcat2 (char *str, char const *str2) {
  return scl_strncat2 (str,
    str2,
    str ? strlen (str) : 0,
    str2 ? strlen (str2) : 0);
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

static uint64_t fasthash64_mix (uint64_t h) {
  h ^= h >> 23;
  h *= 0x2127599bf4325c37ULL;
  h ^= h >> 47;
  return h;
}

static uint64_t fasthash64 (void const *buf, size_t len, uint64_t seed) {
  uint64_t const       m   = 0x880355f21e6d1965ULL;
  uint64_t const      *pos = (uint64_t const *)buf;
  uint64_t const      *end = pos + (len / 8);
  unsigned char const *pos2;
  uint64_t             h = seed ^ (len * m);
  uint64_t             v;

  while (pos != end) {
    v = *pos++;
    h ^= fasthash64_mix (v);
    h *= m;
  }

  pos2 = (unsigned char const *)pos;
  v    = 0;

  switch (len & 7) {
  case 7:
    v ^= (uint64_t)pos2[6] << 48;
  case 6:
    v ^= (uint64_t)pos2[5] << 40;
  case 5:
    v ^= (uint64_t)pos2[4] << 32;
  case 4:
    v ^= (uint64_t)pos2[3] << 24;
  case 3:
    v ^= (uint64_t)pos2[2] << 16;
  case 2:
    v ^= (uint64_t)pos2[1] << 8;
  case 1:
    v ^= (uint64_t)pos2[0];
    h ^= fasthash64_mix (v);
    h *= m;
  }

  return fasthash64_mix (h);
}

unsigned int scl_strhash (char const *str) {
  uint64_t h = fasthash64 (str, strlen (str), 1024);
  return h - (h >> 32);
}

#define HTAB_MIN 2

typedef struct scl_hnode {
  struct scl_hnode *next;
  char const       *key;
  void const       *data;
  unsigned          hash;
} *scl_hnode;

typedef struct scl_htab {
  unsigned char hsz;
  unsigned      hnum;
  scl_hnode    *ht;
} scl_htab;

#define modi(x, y)      ((x) % (y))

#define hisnstrained(t) ((t)->hnum > (1 << ((t)->hsz - 1)))
#define hisnbig(t)      ((t)->hnum > ((t)->hsz >> 3) && (t->hsz > HTAB_MIN))
#define hisoptimal(t) \
  (!hisnstrained (t) && !hisnbig (t) && (t->hsz) >= HTAB_MIN)
#define hoptimal(t)                                   \
  ((scl_log2i ((t)->hnum) + 2 <= HTAB_MIN) ? HTAB_MIN \
                                           : (scl_log2i ((t)->hnum) + 2))
#define hfreenode(n)       (free ((void *)(n)->key), free ((void *)(n)))
#define hnodei(t, hash)    modi (hash, 1 << (t)->hsz)
#define gnodehash(t, hash) ((t)->ht[hnodei (t, hash)])

scl_htab *scl_htabnew() {
  scl_htab *h = (scl_htab *)malloc (sizeof (scl_htab));
  memset (h, 0, sizeof (scl_htab));
  return h;
}

static void scl_htabput (scl_htab *h, scl_hnode node) {
  node->next  = NULL;
  scl_hnode n = gnodehash (h, node->hash);
  while (n && n->next && n->hash != node->hash)
    n = n->next;
  h->hnum++;
  if (!n)
    h->ht[hnodei (h, node->hash)] = node;
  // Replace existing nodes data
  else if (n->hash != node->hash) {
    n->data = node->data;
    hfreenode (node);
  } else
    n->next = node;
}

static void scl_htabrehash (scl_htab *h, scl_hnode *oh, unsigned char ohsz) {
  for (unsigned i = 0; i < ((unsigned)1 << ohsz); i++) {
    scl_hnode n = oh[i];
    for (; n;) {
      scl_hnode next = n->next;
      scl_htabput (h, n);
      n = next;
    }
    oh[i] = NULL;
  }
}

static void scl_htaboptimize (scl_htab *h) {
  scl_hnode    *oh   = h->ht;
  unsigned char ohsz = h->hsz;
  h->hsz             = hoptimal (h);
  unsigned s         = (unsigned)sizeof (scl_hnode) * (1 << h->hsz);
  h->ht              = (scl_hnode *)malloc (s);
  memset (h->ht, 0, s);
  h->hnum = 0;
  if (oh)
    scl_htabrehash (h, oh, ohsz), free ((void *)oh);
}

void scl_htabset (scl_htab *h, char const *key, void const *ptr) {
  if (!hisoptimal (h))
    scl_htaboptimize (h);
  scl_hnode node = malloc (sizeof (struct scl_hnode));
  node->key      = scl_strcopy (key);
  node->data     = ptr;
  node->hash     = scl_strhash (key);
  node->next     = NULL;
  scl_htabput (h, node);
}

void scl_htabremove (scl_htab *h, char const *key) {
  unsigned  hash = scl_strhash (key);
  scl_hnode n    = gnodehash (h, hash);
  while (n && n->next && n->next->hash != hash)
    n = n->next;
  if (n->next && n->next->hash == hash) {
    scl_hnode node = n->next;
    n->next        = node->next;
    hfreenode (node);
    return;
  } else if (n->hash == hash) {
    unsigned i = hnodei (h, hash);
    h->ht[i]   = n->next;
    hfreenode (n);
  }
}

void *scl_htabget (scl_htab const *h, char const *key) {
  unsigned  hash = scl_strhash (key);
  scl_hnode n    = gnodehash (h, hash);
  while (n && n->hash != hash && n->next)
    n = n->next;
  if (n->hash == hash)
    return (void *)n->data;
  return NULL;
}

char const *scl_htabnext (scl_htab const *h, char const *key) {
  if (!h->hnum)
    return NULL;
  if (!key)
    for (unsigned i = 0; i < 1 << h->hsz; i++)
      if (h->ht[i])
        return h->ht[i]->key;
  unsigned  hash = scl_strhash (key);
  scl_hnode n    = gnodehash (h, hash);
  while (n && n->next && n->hash != hash)
    n = n->next;
  // Key does not exist in table
  if (n->hash != hash)
    return NULL;
  // If there is another node in the chain
  if (n->next)
    return n->next->key;
  // Continue on from the next node in the htab array
  for (unsigned i = hnodei (h, hash) + 1; i < 1 << h->hsz; i++)
    if (h->ht[i])
      return h->ht[i]->key;
  // No next node could be found
  return NULL;
}

scl_htab *scl_htabcopy (scl_htab const *h) {
  scl_htab   *out = scl_htabnew();
  char const *k   = NULL;
  while ((k = scl_htabnext (h, k))) {
    void *ptr = scl_htabget (h, k);
    scl_htabset (out, k, ptr);
  }
  return out;
}

unsigned char scl_log2i (unsigned x) {
  unsigned char r = 0;
  while (x >>= 1)
    r++;
  return r;
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
  char *p;
  char *e;
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
  XPATH_ANY,
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

#define XML_MAX_LOST 2048

typedef struct xml_buf {
  char    *buf;
  unsigned used;
  unsigned length;
  unsigned lost;
} xml_buf;

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

#define xview(_p, _e) ((xml_view){.p = (char *)(_p), .e = (char *)(_e)})

static int xml_viewcmp (xml_view sv, xml_view sv2) {
  for (; *sv.p && *sv2.p && sv.p < sv.e && sv2.p < sv2.e && *sv.p != *sv2.p;
       sv.p++, sv2.p++)
    ;
  return *sv.p - *sv2.p;
}

static int xml_viewstrncmp (xml_view sv, char const *str, int n) {
  if (!str)
    return 1;
  for (; n > 0 && sv.p < sv.e && *sv.p != *str; sv.p++, str++, n--)
    ;
  return *sv.p - *str;
}

static int xml_viewstrcmp (xml_view sv, char const *str) {
  if (!sv.p || !str)
    return 1;
  return xml_viewstrncmp (sv, str, strlen (str));
}

#define xml_viewffi(v, c) scl_strnffi (v.p, c, v.e - v.p)

#define xfreeview(v)

#if 0
#  define xrawfree(n)      free ((void *)n)
#  define xrawfreeel(n)    free ((void *)n)
#  define xrawallocel(doc) (xml_elem *)malloc (sizeof (xml_elem))
#else

#  define xrawalloc(doc, s) (scl_pagealloc (&doc->nodes, s))
#  define xrawfreeel(n)
#  define xrawfreeat(a)
#  define xstr2view(v, s)      ((v.p = (char *)s), (v.e = v.p + strlen (v.p)))
#  define xcopyviews(to, from) (*to) = (*from)
#endif


static void xml_free_attr (xml_attr *attr, char mode) {
  if (!attr)
    return;
  xfreeview (attr->data);
  if (mode == XML_FREE_RECURSIVE) {
    for (xml_node *i = attr->next; i;) {
      xml_node *n = i->next;
      xml_free_attr ((xml_attr *)i, XML_FREE_ONLY);
      xrawfreeat (i);
      i = n;
    }
  } else if (mode == XML_FREE_PATCH) {
    if (attr->parent->attr != attr) {
      for (xml_attr *i = attr->parent->attr; i && i->next;)
        if (!xml_viewcmp (i->next->tag, attr->tag))
          i->next = attr->next;
    } else
      attr->parent->attr = (xml_attr *)attr->next;
  }
  xfreeview (attr->tag);
  xrawfreeat (attr);
}

static void xml_free_elem (xml_elem *elem, char mode) {
  if (!elem)
    return;
  xml_free_attr (elem->attr, 1);
  xml_free_elem (elem->child, 1);
  xfreeview (elem->tag);
  xfreeview (elem->data);
  if (mode == XML_FREE_RECURSIVE) {
    for (xml_elem *i = (xml_elem *)elem->next; i;) {
      xml_elem *n = (xml_elem *)i->next;
      xml_free_elem (i, XML_FREE_ONLY);
      i = n;
    }
    elem->next = NULL;
  }
  if (mode != XML_FREE_ONLY) {
    if (elem->parent) {
      for (xml_elem *i = elem->parent->child; i && i->next;)
        if (i == elem) {
          elem->parent->child = (xml_elem *)elem->next;
        } else if ((xml_elem *)i->next == elem)
          i->next = elem->next;
    }
    memset (elem, 0, sizeof (xml_elem));
    xrawfreeel (elem);
  }
}

void xml_free_doc (xml_doc *doc) {
  if (!doc)
    return;
  xml_free_elem ((xml_elem *)doc, XML_FREE_RECURSIVE);
  scl_freepages (&doc->txt);
  scl_freepages (&doc->nodes);
}

void xml_add_attr (xml_elem *elem, xml_attr *attr) {
  if (!elem || !attr)
    return;
  if (elem->attr) {
    xml_node *i = (xml_node *)elem->attr;
    for (; i && i->next; i = i->next) {
      if (!xml_viewcmp (i->tag, attr->tag)) {
        i->data = attr->data;
        xml_free_attr (attr, XML_FREE_ONLY);
        return;
      }
    }
    i->next = (xml_node *)attr;
  } else
    elem->attr = attr;
  attr->parent = elem;
}

void xml_add_elem (xml_elem *elem, xml_elem *child) {
  if (!elem || !child)
    return;
  child->parent = elem;
  if (elem->child) {
    elem = elem->child;
    if (elem->tail)
      elem->tail->next = (xml_node *)child, elem->tail = (xml_elem *)child;
    else
      elem->next = (xml_node *)child, elem->tail = (xml_elem *)child;
  } else {
    xml_free_elem ((xml_elem *)child->next, XML_FREE_RECURSIVE);
    child->next = NULL;
    elem->child = child;
  }
}

static void xml_add_next (xml_elem *elem, xml_elem *next) {
  if (!elem || !next)
    return;
  next->parent = elem->parent;
  if (elem->tail)
    elem->tail->next = (xml_node *)next, elem->tail = (xml_elem *)next;
  else
    elem->next = (xml_node *)next, elem->tail = (xml_elem *)next;
}

#define SPACEBIT 1
#define ALPHABIT 2
#define DIGITBIT 4

/* clang-format off */
static char const xctypes[] = {
  /* 1 */
  0,0,0,0,0,0,0,0, /* 0-7*/
  0,0,1,0,0,1,0,0, /* 8-15 */
  /* 2 */
  0,0,0,0,0,0,0,0, /* 16-23 */
  0,0,0,0,0,0,0,0, /* 24-31 */
  /* 3 */
  1,0,0,0,0,0,0,0, /* 32-39 */
  0,0,0,0,0,0,0,0, /* 40-47 */
  /* 4 */
  4,4,4,4,4,4,4,4, /* 48-55 */
  4,4,0,0,0,0,0,0, /* 56-63 */
  /* 5 */
  0,2,2,2,2,2,2,2, /* 64-71 */
  2,2,2,2,2,2,2,2, /* 72-79 */
  /* 6 */
  2,2,2,2,2,2,2,2, /* 80-87 */
  2,2,2,0,0,0,0,2, /* 88-95 */
  /* 7 */
  0,2,2,2,2,2,2,2, /* 96-103 */
  2,2,2,2,2,2,2,2, /* 104-111 */
  /* 8 */
  2,2,2,2,2,2,2,2, /* 112-119 */
  2,2,2,0,0,0,0,0, /* 120-127 */

  /* 128-255 */
  2,0,0,0,0,0,0,0, /* 0-7*/
  0,0,0,0,0,0,0,0, /* 8-15 */
  /* 2 */
  0,0,0,0,0,0,0,0, /* 16-23 */
  0,0,0,0,0,0,0,0, /* 24-31 */
  /* 3 */
  0,0,0,0,0,0,0,0, /* 32-39 */
  0,0,0,0,0,0,0,0, /* 40-47 */
  /* 4 */
  0,0,0,0,0,0,0,0, /* 48-55 */
  0,0,0,0,0,0,0,0, /* 56-63 */
  /* 5 */
  0,0,0,0,0,0,0,0, /* 64-71 */
  0,0,0,0,0,0,0,0, /* 72-79 */
  /* 6 */
  0,0,0,0,0,0,0,0, /* 80-87 */
  0,0,0,0,0,0,0,0, /* 88-95 */
  /* 7 */
  0,0,0,0,0,0,0,0, /* 96-103 */
  0,0,0,0,0,0,0,0, /* 104-111 */
  /* 8 */
  0,0,0,0,0,0,0,0, /* 112-119 */
  0,0,0,0,0,0,0,0, /* 120-127 */
};
/* clang-format on */

#define xisalnum(c) (xctypes[c] & (ALPHABIT | DIGITBIT))
#define xisdigit(c) (xctypes[c] & DIGITBIT)
#define xisspace(c) (xctypes[c] & SPACEBIT)

#define xskipspace(p)   \
  while (xisspace (*p)) \
  p++

static int xml_parse_textchar (char const *s, char const **ep, char *out) {
  if (*s != '&') {
    return ((*ep)++), (*out = *s), 1;
  } else {
    s++;
    if (!strncmp (s, "lt;", 3))
      return ((*ep) += 4), (*out = '<'), 1;
    if (!strncmp (s, "gt;", 3))
      return ((*ep) += 4), (*out = '>'), 1;
    if (!strncmp (s, "amp;", 4))
      return ((*ep) += 5), (*out = '&'), 1;
    if (!strncmp (s, "apos;", 5))
      return ((*ep) += 6), (*out = '\''), 1;
    if (!strncmp (s, "quot;", 5))
      return ((*ep) += 6), (*out = '\"'), 1;
    return ((*ep)++), 1;
  }
}

static xml_view xml_parse_text (char const *s, char const **ep, char delim) {
  char const *p = s;
  while (*p && *p != delim)
    p++;
  return ((*ep) = p), xview (s, p);
}

static xml_attr *xml_parse_attr (xml_doc *doc, char const *s, char const **ep) {
  xml_attr    attr;
  char const *p = s;
  if (!xisalnum (*p))
    return NULL;
  memset (&attr, 0, sizeof (attr));
  do
    p++;
  while (xisalnum (*p));
  attr.tag = xview (s, p);
  if (p[0] != '=' && p[1] != '\"' && p[1] != '\'')
    return NULL;
  char delim = p[1];
  s          = (p += 2);
  attr.data  = xml_parse_text (s, &p, delim);
  return ((*ep) = ++p), xml_copy_attribute (doc, &attr);
}

static xml_elem *xml_parse_elem (xml_doc *doc, xml_elem *parent, char const *s,
  char const **ep) {
  static int  leave = 0;
  char const *p     = s;
  xskipspace (p);
  s = p;
  if (*p != '<')
    return NULL;
  xml_elem *elem = xrawalloc (doc, sizeof (xml_elem));
  memset (elem, 0, sizeof (xml_elem));
  elem->parent = parent;
  s            = ++p;
  if (*p == '/')
    goto end_elem;
  if (*p == '?')
    goto prelude_elem;
  while (xisalnum (*p))
    p++;
  if (s == p)
    return NULL;
  elem->tag = xview (s, p);
  xskipspace (p);
  while (*p != '>' && *p != '/' && *p) {
    xml_attr *attr = xml_parse_attr (doc, p, &p);
    if (attr)
      xml_add_attr (elem, attr);
    xskipspace (p);
  }
  if (*p == '>') {
    p++;
    if (*p != '<')
      elem->data = xml_parse_text (p, &p, '<');
    while (1) {
      s               = p;
      xml_elem *celem = xml_parse_elem (doc, elem, p, &p);
      if (celem)
        xml_add_elem (elem, celem);
      else if (leave) {
        leave = 0;
        break;
      } else
        return NULL;
    }
    return ((*ep) = p), elem;
  } else if (*p == '/' || leave) {
    p += 1 + (*p == '/');
    leave = 0;
    s     = p;
    return ((*ep) = p), elem;
  }
  return NULL;
end_elem:
  s = ++p;
  while (xisalnum (*p))
    p++;
  xml_view tv = xview (s, p);
  if (!xml_viewcmp (parent->tag, tv))
    return (leave |= 1), ((*ep) = ++p), NULL;
  else
    return NULL;
prelude_elem:
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

xml_doc *xml_parse_string (char const *str) {
  xml_doc doc;
  memset (&doc, 0, sizeof (doc));
  unsigned l = strlen (str);
  scl_pageset (&doc.txt, l + 1);
  if (!doc.txt.data)
    return NULL;
  char *p = scl_pagealloc (&doc.txt, l + 1);
  memcpy (p, str, l);
  p[l]           = 0;
  xml_elem *root = xml_parse_elem (&doc, NULL, p, (char const **)&p);
  if (!root) {
    scl_freepages (&doc.txt);
    scl_freepages (&doc.nodes);
    return NULL;
  }
  memcpy (&doc, root, sizeof (xml_elem));
  xrawfreeel (root);
  xml_doc *copy = (xml_doc *)malloc (sizeof (xml_doc));
  memcpy (copy, &doc, sizeof (xml_doc));
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
  xstr2view (elem.tag, scl_strcopy (tag));
  if (str)
    xstr2view (elem.data, scl_strcopy (str));
  return memcpy (xrawalloc (doc, sizeof (xml_elem)), &elem, sizeof (elem));
}

xml_elem *xml_copy_elem (xml_doc *doc, xml_elem *elem) {
  if (!elem)
    return NULL;
  xml_elem *copy = xrawalloc (doc, sizeof (xml_elem));
  memcpy (copy, elem, sizeof (xml_elem));
  xcopyviews (copy, elem);
  return copy;
}

void xml_replace_elem (xml_elem *elem, xml_elem *with) {
  if (!elem || !with)
    return;
  if (with) {
    xml_free_elem (elem->child, XML_FREE_RECURSIVE);
    xfreeview (elem->tag);
    xfreeview (elem->data);
    memcpy (elem, with, sizeof (xml_elem));
    xrawfreeel (with);
  } else {
    xml_free_elem (elem, XML_FREE_PATCH);
  }
}

xml_attr *xml_str_attribute (char const *tag, char const *str) {
  if (!tag || !str)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  xstr2view (attr.tag, scl_strcopy (tag));
  xstr2view (attr.data, scl_strcopy (str));
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_int_attribute (char const *tag, int i) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  xstr2view (attr.tag, scl_strcopy (tag));
  xstr2view (attr.data, scl_fmt ("%i", i));
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_float_attribute (char const *tag, float n) {
  if (!tag)
    return NULL;
  xml_attr attr;
  memset (&attr, 0, sizeof (attr));
  xstr2view (attr.tag, scl_strcopy (tag));
  xstr2view (attr.data, scl_fmt ("%f", n));
  xml_attr *copy = (xml_attr *)malloc (sizeof (attr));
  memcpy (copy, &attr, sizeof (attr));
  return copy;
}

xml_attr *xml_copy_attribute (xml_doc *doc, xml_attr *attr) {
  if (!attr)
    return NULL;
  xml_attr *copy = xrawalloc (doc, sizeof (xml_attr));
  memcpy (copy, attr, sizeof (xml_attr));
  xcopyviews (copy, attr);
  return copy;
}

xml_attr *xml_find_attribute (xml_elem *elem, char const *tag) {
  if (!elem || !elem->attr || !tag)
    return NULL;
  xml_view tv = xview (tag, strlen (tag));
  for (xml_attr *attr = elem->attr; attr; attr = (xml_attr *)attr->next)
    if (!xml_viewcmp (attr->tag, tv))
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
  for (; p < v.e; p++) {
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
  char        noapos    = xml_viewffi (attr->data, "\'") == -1;
  char        noquot    = xml_viewffi (attr->data, "\"") == -1;
  char        aposdelim = (noapos && !noquot) ? 1 : 0;
  char const *q         = !aposdelim ? "\"" : "\'";
  char const *q2        = !aposdelim ? "=\"" : "=\'";
  xml_napp (out, wp, size, " ", 1);
  xml_napp (out, wp, size, attr->tag.p, attr->tag.e - attr->tag.p);
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
  for (; ielem && ielem->tag.p; ielem = (xml_elem *)ielem->next) {
    xml_napp (out, wp, size, "<", 1);
    xml_napp (out, wp, size, ielem->tag.p, ielem->tag.e - ielem->tag.p);
    if (ielem->attr) {
      xml_attr *attr = ielem->attr;
      for (; attr; attr = (xml_attr *)attr->next)
        xml_print_attr (attr, out, wp, size);
    }
    if (ielem->child || isroot || ielem->data.p) {
      xml_napp (out, wp, size, ">", 1);
      if (ielem->data.p)
        xml_print_string (ielem->data, out, wp, size, 0);
      xml_print_elem (ielem->child, out, wp, size, 0);
      xml_napp (out, wp, size, "</", 2);
      xml_napp (out, wp, size, ielem->tag.p, ielem->tag.e - ielem->tag.p);
      xml_napp (out, wp, size, ">", 1);
    } else {
      xml_napp (out, wp, size, "/>", 2);
    }
  }
  return 1;
}

char const *xml_print (xml_doc *doc) {
  if (!doc)
    return NULL;

  // char const prologue[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  char const prologue[] = "";
  int        size       = 512;
  char      *out        = (char *)malloc (size);
  memset (out, 0, size);
  memcpy (out, prologue, sizeof (prologue) - 1);
  char *wp = out + sizeof (prologue) - 1;
  xml_print_elem ((xml_elem *)doc, &out, &wp, &size, 1);
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
  while (xisalnum (*p2) || (*p2 == '*' && *(p2 - 1) != '*'))
    p2++;
  xml_view v = xview (s2, p2 - s2);
  if (xml_viewstrncmp (v, "*", 1)) {
    *view = v;
  }
  *s = s2;
  *p = p2;
  // e.tag is already null for * case
}

xpath_exp *xml_xpath (char const *exp) {
  char      *s = (char *)exp, *p = (char *)exp;
  xpath_exp *top  = NULL;
  xpath_exp *last = NULL;
  while (*p) {
    s = p;
    xpath_exp e;
    memset (&e, 0, sizeof (e));
    // Path exp
    if (*p == '/') {
      // Post attr paths are forbidden
      if (last &&
          (last->type == XPATH_EXP_ATAG || last->type == XPATH_EXP_RATAG))
        return NULL;
      if (p[1] != '/') {
        // Element
        if (p[1] != '@') {
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
        if (p[1] != '@') {
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
      if (xisalnum (p[1])) {
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
        } else
          math.op = XPATH_ANY;
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
        e.math = math;
        goto post_exp;
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
    xpath_exp *copy = (xpath_exp *)malloc (sizeof (e));
    memcpy (copy, &e, sizeof (e));
    if (top)
      last->sub = copy, last = copy;
    else
      top = copy, last = copy;
  }
  return top;
}

void xml_eval (xpath_exp *xpath) {
}
