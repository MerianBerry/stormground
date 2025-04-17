#pragma once

#if defined(__unix__) || defined(__APPLE__)
#  define _THEPOSIX 1
#  include <unistd.h>
#elif defined(_WIN32)
#  define _THEWINDOWS 1
#  include "resources/rc.h"

#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "scl.h"

#define SG_MAJOR         1
#define SG_MINOR         2
#define SG_VERNAME       "1.4"

#define SG_GAMEPAD_LAST  GLFW_JOYSTICK_8

#define SG_MAX_MONHEIGHT 720
#define SG_MAX_MONWIDTH  1280

#define SG_MAX_PEELS     8

#define SG_MIN_VERTS     8
#define SG_MAX_VERTS     24

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

typedef struct SGpos {
  unsigned short x;
  unsigned short y;
  unsigned short d;
} SGpos;

typedef struct SGvertex {
  SGpos   p;
  SGcolor c;
} SGvertex;

typedef struct SGrenderPipe {
  SGvertex* vbuf;
  unsigned  texs[4];
  unsigned  fbos[2];
  unsigned  vbo, vao, udepth, uscreen;
  unsigned  program;
  unsigned  verts;
  char      npeels;
} SGrenderPipe;

typedef struct Gamepad {
  GLFWgamepadstate gstate;
  char             buttons[GLFW_GAMEPAD_BUTTON_LAST + 1];
  char*            name;
  char             connected;
} Gamepad;

typedef struct SGstate {
  Gamepad      gpads[SG_GAMEPAD_LAST + 1];
  char         keys[GLFW_KEY_LAST + 1];
  int          activeGpads[SG_GAMEPAD_LAST + 1];
  char         buttons[GLFW_MOUSE_BUTTON_LAST + 1];
  SGrenderPipe rp;
  scl_htab*    mappings;
  scl_htab*    bmaps;
  GLFWwindow*  win;
  char const*  projectDir;
  char*        name;
  SGscript*    main;
  double       tfps;
  double       time;
  double       realCurX, realCurY;
  double       fakeCurX, fakeCurY;
  int          runstate;
  float        aspect;
  int          width;
  int          height;
  int          curx;
  int          cury;
  int          scrollx, scrolly;
  SGcolor      col;
  float        delta;
  char         usage;
} SGstate;

enum {
  SG_RUNSTATE_STOP = 1,
  SG_USAGE_MANDK   = 0,
  SG_USAGE_GAMEPAD,
};

int sgRunCli (SGstate* sgs, int argc, char** argv);

int sgGetProjectSets (SGstate* sgs);
