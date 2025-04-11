#include "sg_log.h"
#include "scl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static scl_file* log_   = NULL;
static char      trylog = 1;
static char*     error  = NULL;
static char      doecho = 0;

char const* sg_setError (char const* msg) {
  if (!msg)
    return NULL;
  size_t l   = strlen (msg);
  char*  buf = malloc (l + 1);
  memcpy (buf, msg, l + 1);
  error = buf;
  return error;
}

char const* sg_getError() {
  return error;
}

void sg_echo (char echo) {
  doecho = echo;
}

static int sg_preLog() {
  if (!log_ && trylog) {
    char const* exdir = scl_execdir();
    log_              = scl_openf ("w", "%s/storm.log", exdir);
    trylog            = !log_;
  }
  return !trylog;
}

static void sg_log (char const* source, char const* severity, char const* msg) {
  if (!sg_preLog() || !source || !msg)
    return;
  time_t     t       = time (NULL);
  struct tm* tm_info = localtime (&t);

  char buffer[256];
  strftime (buffer, sizeof (buffer), "[%H:%M:%S]", tm_info);

  char const* str = scl_fmt ("%s [%s/%s]: %s\n", buffer, source, severity, msg);
  scl_write_str (log_, str);
  free ((void*)str);

  if (doecho) {
    fprintf (stderr, "%s\n", msg);
  }
}

void sg_logInfo (char const* source, char const* msg) {
  sg_log (source, "INFO", msg);
}

void sg_logWarn (char const* source, char const* msg) {
  sg_log (source, "WARN", msg);
}

void sg_logError (char const* source, char const* msg) {
  sg_setError (msg);
  sg_log (source, "Error", msg);
}

void sg_logInfof (char const* source, char const* fmt, ...) {
  va_list args;
  va_start (args, fmt);
  char const* msg = scl_vfmt (fmt, args);
  va_end (args);
  sg_logInfo (source, msg);
  free ((void*)msg);
}

void sg_logWarnf (char const* source, char const* fmt, ...) {
  va_list args;
  va_start (args, fmt);
  char const* msg = scl_vfmt (fmt, args);
  va_end (args);
  sg_logWarn (source, msg);
  free ((void*)msg);
}

void sg_logErrorf (char const* source, char const* fmt, ...) {
  va_list args;
  va_start (args, fmt);
  char const* msg = scl_vfmt (fmt, args);
  va_end (args);
  sg_logError (source, msg);
  free ((void*)msg);
}
