#pragma once

#if defined(__unix__) || defined(__APPLE__)
#define _THEPOSIX 1
#  include <unistd.h>
#elif defined(_WIN32)
#define _THEWINDOWS 1
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define HYDROGEN_ALL
#include "hydrogen/hydrogen.h"

#define SG_MAJOR        1
#define SG_MINOR        2
#define SG_VERNAME      "1.2"

#define SG_GAMEPAD_LAST GLFW_JOYSTICK_8

typedef struct lua_State lua_State;

typedef struct SGscript {
  lua_State* L;

} SGscript;

typedef struct SGcolor {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} SGcolor;

typedef struct SGimage {
  uint8_t* data;
  int      width;
  int      height;
  int      channels;
  int      tex;
  char     type;
} SGimage;

typedef struct SGtexture {
  uint32_t tex;
  int      format;
  int      w;
  int      h;
  short    min_filt;
  short    mag_filt;
  short    wrap_s;
  short    wrap_t;
} SGtexture;

typedef struct SGtriangle {
  h_vec2  p1;
  h_vec2  p2;
  h_vec2  p3;
  SGcolor c;
} SGtriangle;

enum {
  SG_PRIMITIVE_RECT     = 0,
  SG_PRIMITIVE_CIRCLE   = 1,
  SG_PRIMITIVE_TRIANGLE = 2,
  SG_PRIMITIVE_LINE = 3,
};

typedef struct SGprimitive {
  float  c[3];
  h_vec2 p1;
  h_vec2 p2;
  h_vec2 p3;
  h_vec2 p4;
  int    t;
} SGprimitive;

typedef struct SSBO {
  float       time;
  int         primc;
  SGprimitive primv[0xffff];
} SSBO;

typedef struct Gamepad {
  GLFWgamepadstate gstate;
  char             buttons[GLFW_GAMEPAD_BUTTON_LAST + 1];
  char*            name;
  char             connected;
} Gamepad;

typedef struct SGstate {
  Gamepad     gpads[SG_GAMEPAD_LAST + 1];
  char        keys[GLFW_KEY_LAST + 1];
  int         activeGpads[SG_GAMEPAD_LAST + 1];
  SGtexture   mon;
  char        buttons[GLFW_MOUSE_BUTTON_LAST + 1];
  GLFWwindow* win;
  char*       projectDir;
  h_buffer    projectFileContent;
  char*       name;
  SGscript*   main;
  SSBO*       ssbo;
  double      tfps;
  double      time;
  double      realCurX, realCurY;
  double      fakeCurX, fakeCurY;
  int         runstate;
  int         width;
  int         height;
  int         curx;
  int         cury;
  int         scrollx, scrolly;
  SGcolor     col;
  float       delta;
  char        usage;
} SGstate;

enum {
  SG_RUNSTATE_STOP = 1,
  SG_USAGE_MANDK   = 0,
  SG_USAGE_GAMEPAD,
};
