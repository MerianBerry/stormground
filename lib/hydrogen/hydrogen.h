#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef HYDROGEN_ALL
#  define HYDROGEN_TIME
#  define HYDROGEN_AVL
#  define HYDROGEN_STRING
#  define HYDROGEN_IO
#  define HYDROGEN_MEM
#  define HYDROGEN_VECTOR
#  define HYDROGEN_MATH
#endif

/* Opaque module structure */
typedef struct fu_module fu_module;

typedef unsigned char fu_byte;

#ifdef HYDROGEN_TIME
enum {
  seconds_e      = 1,
  milliseconds_e = 1000,
  microseconds_e = 1000000,
  nanoseconds_e  = 1000000000,
};

typedef struct h_timepoint {
#  if defined(_WIN32)
  double freq;
  long   c;
#  elif defined(__GNUC__)
  long s;
  long ns;

#  endif
} h_timepoint;

typedef struct timespec timespec_t;

void microsleep (long usec);

h_timepoint timenow();

double timeduration (h_timepoint end, h_timepoint start, double ratio);

void wait (double seconds);
void waitms (double ms);
#endif

#ifdef HYDROGEN_AVL
typedef struct avl_node_s {
  char *key;
  void *mem;

  struct avl_node_s *parent;

  struct avl_node_s *left;
  struct avl_node_s *right;
} avl_node_t;

typedef struct avl_tree_s {
  avl_node_t *root;
  size_t      size;
} avl_tree_t;

int avl_height (avl_node_t *base);

int avl_findbalance (avl_node_t *base);

avl_node_t **avl_fside (avl_node_t *parent, avl_node_t *target);

void avl_leftrot (avl_node_t *X, avl_node_t *Z);

void avl_rightrot (avl_node_t *X, avl_node_t *Z);

void avl_balance (avl_tree_t *bintree, avl_node_t *base);

void avl_create (avl_tree_t *bintree, avl_node_t **target, avl_node_t *parent,
                 char const *key, void *mem);

avl_node_t *avl_find (avl_tree_t *bintree, char const *key);

void avl_append (avl_tree_t *bintree, char const *key, void *mem);

void avl_destroysubtree (avl_tree_t *tree, avl_node_t *root);

void avl_free (avl_tree_t **bintree);

void avl_freeX (avl_tree_t *bintree);

void avl_destroynode (avl_tree_t *tree, avl_node_t *node);

void avl_clear (avl_tree_t *bintree);

avl_tree_t *avl_newtree();
#endif

#ifdef HYDROGEN_STRING
#  define STR_MAX 0x7fffffff
#  include <stdarg.h>
#  define npos ((size_t)-1)

char *str_add (char *lhs, char const *rhs);

char *str_substr (char const *src, size_t off, size_t len);

size_t str_ffo (char const *str, char c);

size_t str_flo (char const *str, char c);

size_t str_flox (char const *str, char const *cs);

size_t str_ffi (char const *str, char const *cmp);

size_t str_fli (char const *str, char const *cmp);

unsigned long str_hash (char const *str);

char *str_fmtv (char const *fmt, va_list args);

char *str_fmt (char const *fmt, ...);

char const *str_cpy (char const *src, size_t bytes);

char *str_append (char *src, char const *nstr, size_t bytes);

/*
 * Replaces a section of `src` with `str`
 * `src` source string for the replacing operation
 * `off` dictates the start of the replacing operation
 * `len` dictates how many bytes to replace (when 0, no bytes are removed from
 * `src`) `str` content replacing content in `src`
 */
char *str_replace (char const *src, long off, long len, char const *str);

char *str_colorfmtv (char const *src, va_list args);

char *str_colorfmt (char const *src, ...);

int utf8_charsize (fu_byte c);

long utf8_strlen (char const *str);

/*
 * Returns the actual offset of the `off` character position in `str`
 */
long utf8_actual (char const *str, long off);

int utf8_encode (int utf);

int utf8_decode (int utf8);

int utf8_swap (int utf8);

int utf8_literal (int utf);

char *utf8_tostring (int utf8);

int errorfv (char const *fmt, va_list args);

int errorf(const char* fmt, ...);

int warningfv (char const *fmt, va_list args);

int warningf (char const *fmt, ...);
#endif

#ifdef HYDROGEN_IO
typedef struct h_buffer {
  void  *data;
  size_t size;
} h_buffer;

#  ifdef UNDEP_DIRENT
#    ifndef NO_DIRENT
#      define USE_DIRENT
typedef struct dirent dirent_t;
int io_scandir (char const *dir, dirent_t ***pList, int *pCount);
#    endif
#  endif

char *io_fixhome (char const *path);

char io_direxists (char const *path);

char io_exists (char const *path);

void io_mkdir (char const *path);

h_buffer io_read (char const *path);
#endif

#ifdef HYDROGEN_MEM
void *mem_grow (void *src, int stride, int len, void *newData, int newDataLen);

void *mem_copy (void *src, int size);
#endif

#ifdef HYDROGEN_VECTOR
#  ifndef HYDROGEN_MATH
#    define HYDROGEN_MATH
#  endif

typedef struct h_vec2 {
  float x;
  float y;
} h_vec2;

typedef struct h_vec3 {
  float x;
  float y;
  float z;
} h_vec3;

float distance2d (h_vec2 v);

float distance3d (h_vec3 v);

float dir2d (h_vec2 v);

h_vec2 plus2d (h_vec2 a, h_vec2 b);

h_vec2 sub2d (h_vec2 a, h_vec2 b);

h_vec2 mag2d (h_vec2 v, float m);

h_vec2 normalize2d (h_vec2 v);

h_vec3 normalize3d (h_vec3 v);

float dot2d (h_vec2 a, h_vec2 b);

float dot3d (h_vec3 a, h_vec3 b);
#endif

#ifdef HYDROGEN_MATH
int powi (int x, int y);

double minf (double x, double y);

double maxf (double x, double y);

float clampf (float x, float y, float z);

int mini (int x, int y);

int maxi (int x, int y);

int clampi (int x, int y, int z);
#endif
