#ifndef SG_LOG_H
#define SG_LOG_H

#include <stdarg.h>

#define sg_echoError(msg)  \
  sg_echo (1);             \
  sg_logError ("sg", msg); \
  sg_echo (0)

char const *sg_getError();

void sg_echo (char echo);

void sg_logInfo (char const *source, char const *msg);

void sg_logWarn (char const *source, char const *msg);

void sg_logError (char const *source, char const *msg);

void sg_logInfof (char const *source, char const *fmt, ...);

void sg_logWarnf (char const *source, char const *fmt, ...);

void sg_logErrorf (char const *source, char const *fmt, ...);

#endif