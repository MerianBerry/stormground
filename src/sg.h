#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define HYDROGEN_ALL
#include "hydrogen/hydrogen.h"

#define SG_MAJOR 0
#define SG_MINOR 1

#define binary(name)                           \
  extern char        _binary_##name##_start[]; \
  extern char        _binary_##name##_end[];   \
  static int         name##_size;              \
  static char const* name##_start = _binary_##name##_start

#define resolve_binary_size(name) \
  name##_size = _binary_##name##_end - _binary_##name##_start

typedef struct SGstate {
  int         runstate;
  GLFWwindow* win;
  char*       projectDir;
  double      tfps;
  char        keys[GLFW_KEY_LAST];
  char        buttons[GLFW_MOUSE_BUTTON_LAST];
} SGstate;

enum {
  runstate_stop = 1,
};