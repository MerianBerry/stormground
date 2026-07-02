#pragma once

#include "glad/gl.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include "scl.h"
#include "keycodes.h"

#define SG_MAJOR       1
#define SG_MINOR       5
#define SG_VERNAME     "1.5"

#define SG_BUTTON_LAST 4

// 2 gamepads max
#define SG_GAMEPAD_LAST  1

#define SG_MAX_MONHEIGHT 1080
#define SG_MAX_MONWIDTH  1920

#define SG_MAX_PEELS     8

#define SG_MIN_VERTS     8
#define SG_MAX_VERTS     22

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

typedef struct SGvertex {
  short          p[2];
  unsigned short d;
  SGcolor        c[4];
} SGvertex;

typedef struct SGrenderPipe {
  SGvertex*      vbuf;
  unsigned       texs[4];
  unsigned       fbos[2];
  unsigned       vbo, vao, vb2, va2, uscreen, utex;
  unsigned       program, blit;
  unsigned       verts;
  SGcolor        ccol;
  unsigned short cd;
  char           npeels;
} SGrenderPipe;

typedef struct Gamepad {
  SDL_Gamepad* gp;
  char         buttons[SDL_GAMEPAD_BUTTON_COUNT];
  float        axes[SDL_GAMEPAD_AXIS_COUNT];
  char*        name;
  char         connected;
} Gamepad;

extern struct SGstate {
  Gamepad gpads[SG_GAMEPAD_LAST + 1];
  int     activeGpads[SG_GAMEPAD_LAST + 1];
  char    keys[SG_KEY_LAST + 1];
  // 5 mouse buttons
  char          buttons[SG_BUTTON_LAST + 1];
  SGrenderPipe  rp;
  scl_htab*     mappings;
  scl_htab*     bmaps;
  SDL_Window*   win;
  SDL_GLContext ctx;
  const char*   projectDir;
  char*         name;
  SGscript*     main;
  double        tfps;
  double        time;
  double        realCurX, realCurY;
  double        fakeCurX, fakeCurY;
  int           runstate;
  float         aspect;
  int           width;
  int           height;
  int           curx;
  int           cury;
  float         scrollx, scrolly;
  int           winw, winh;
  SGcolor       col;
  float         delta;
  char          usage;
} _state;

enum {
  SG_RUNSTATE_STOP = 1,
  SG_USAGE_MANDK = 0,
  SG_USAGE_GAMEPAD,
};

int sgRunCli(int argc, char** argv);
