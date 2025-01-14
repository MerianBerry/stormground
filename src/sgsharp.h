#ifndef SG_SHARP_H
#define SG_SHARP_H

int sgsharp_new (char const* dir, char const* name);

int sgsharp_build (char const* dir);

char const* sgsharp_get_assembly (char const* dir);
#endif
