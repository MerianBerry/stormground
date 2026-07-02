#include "sgrender.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "minilua.h"
#include "sgapi.h"
#include "sgimage.h"
#include "sgshader.h"
// Generated
#include "blit_frag.h"
#include "blit_vert.h"
#include "main_frag.h"
#include "main_vert.h"

/* DEPTH PEELING OIT RENDERING:
  using a "custom" depth buffer, we render
  using depth testing of GL_LESS/GL_LEQUAL, and a manual
  shader depth test.

  The shader depth test will the bound depth buffer, and perform
  a greater than depth test, and throw away all other fragments.

  Note that the shader side depth texture must be readonly, so it must
  be a copy of the framebuffers depth texture, at the time of rendering.

  When a fragment isnt thrown away, it can be blended onto the current
  color texture, but not in a way that overrides the existing color.


  VIEWPORT:

  Pretty simple. Instead of resizing the "virtual monitor" every resize,
  just start with a texture at the max size, and set the viewport.

  HOLLOW SHAPES:

  ???

  CIRCLES:

  Use the drawArc algorithm to construct triangles.

  TEXT:

  Similar to how it was previously, it would just be easier to create
  rectangles to form the characters.

*/

static SGvertex const base[] = {
    {.p = {0, 0}, 997, .c = {255, 0, 0, 255}},
    {.p = {96, 0}, 997, .c = {255, 0, 0, 255}},
    {.p = {0, 96}, 997, .c = {255, 0, 0, 255}},
    {.p = {0, 0}, 998, .c = {0, 255, 0, 128}},
    {.p = {96, 0}, 998, .c = {0, 255, 0, 128}},
    {.p = {96, 96}, 998, .c = {0, 255, 0, 128}},
    {.p = {36, 0}, 999, .c = {0, 0, 255, 32}},
    {.p = {36, 96}, 999, .c = {0, 0, 255, 32}},
    {.p = {96, 96}, 999, .c = {0, 0, 255, 32}},
};

static const struct {
  float p[2];
  float uv[2];
} quadbuf[] = {{{-1, -1}, {0, 0}}, {{1, -1}, {1, 0}}, {{1, 1}, {1, 1}},
               {{-1, -1}, {0, 0}}, {{1, 1}, {1, 1}},  {{-1, 1}, {0, 1}}};

#define SG_DEPTH 0
#define SG_COLOR 1
#define SG_DCOPY 2
#define SG_CCOPY 3

#define SG_FBO 0
#define SG_FCOPY 1

int sgInitRenderPipe() {
  unsigned vbo, vao, vb2, va2, fbo;

  // MAIN SHADER PROGRAM
  uint32_t vShader = sgCompileShader(GL_VERTEX_SHADER, (char const *)main_vert,
                                     sizeof(main_vert) - 1);
  if (!vShader)
    return 3;

  uint32_t fShader = sgCompileShader(
      GL_FRAGMENT_SHADER, (char const *)main_frag, sizeof(main_frag) - 1);
  if (!fShader)
    return 3;

  unsigned shaders[] = {vShader, fShader};
  unsigned prog = sgLinkShaderProgram(shaders, 2);
  if (!prog)
    return 4;
  glDeleteShader(vShader);
  glDeleteShader(fShader);
  _state.rp.uscreen = glGetUniformLocation(prog, "screen");
  _state.rp.program = prog;

  // BLIT SHADER PROGRAM
  vShader = sgCompileShader(GL_VERTEX_SHADER, (char const *)blit_vert,
                            sizeof(blit_vert) - 1);
  if (!vShader)
    return 3;
  fShader = sgCompileShader(GL_FRAGMENT_SHADER, (char const *)blit_frag,
                            sizeof(blit_frag) - 1);
  if (!fShader)
    return 3;
  shaders[0] = vShader, shaders[1] = fShader;
  prog = sgLinkShaderProgram(shaders, 2);
  if (!prog)
    return 4;
  glDeleteShader(vShader);
  glDeleteShader(fShader);
  _state.rp.blit = prog;
  _state.rp.utex = glGetUniformLocation(prog, "tex");

  unsigned texs[4];
  glGenTextures(4, texs);
  glBindTexture(GL_TEXTURE_2D, texs[SG_DEPTH]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SG_MAX_MONWIDTH + 20,
               SG_MAX_MONHEIGHT + 20, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, texs[SG_COLOR]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SG_MAX_MONWIDTH + 20,
               SG_MAX_MONHEIGHT + 20, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned fbos[2];
  glGenFramebuffers(2, fbos);

  glBindFramebuffer(GL_FRAMEBUFFER, fbos[SG_FBO]);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         texs[SG_DEPTH], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texs[SG_COLOR], 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return fprintf(stderr, "Framebuffers are not complete.\n"), 4;

  int const n = 1 << SG_MAX_VERTS;
  SGvertex *buf = malloc(sizeof(SGvertex) * n);
  if (!buf) {
    fprintf(stderr, "Out of memory\n");
    // Just exit here. There is no recovering.
    exit(1);
  }
  _state.rp.vbuf = buf;
  // memcpy (buf, base, sizeof (base));
  // _state.rp.verts += sizeof (base) / sizeof (base[0]);

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(SGvertex) * n, buf, GL_DYNAMIC_DRAW);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, sizeof(SGvertex), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 1, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(SGvertex),
                        (void *)4);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SGvertex),
                        (void *)6);

  glGenVertexArrays(1, &va2);
  glGenBuffers(1, &vb2);
  glBindBuffer(GL_ARRAY_BUFFER, vb2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float[4]) * 6, quadbuf, GL_STATIC_DRAW);
  glBindVertexArray(va2);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]),
                        (void *)sizeof(float[2]));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // glEnable (GL_FRAMEBUFFER_SRGB);

  // _state.rp.npeels = 6;

  _state.rp.vbo = vbo;
  _state.rp.vao = vao;
  _state.rp.vb2 = vb2;
  _state.rp.va2 = va2;
  memcpy(_state.rp.fbos, fbos, sizeof(fbos));
  memcpy(_state.rp.texs, texs, sizeof(texs));
  _state.rp.cd = 0;
  return 0;
}

int sgDrawRenderPipe() {
#if 0
  memcpy(_state.rp.vbuf, base, sizeof(base));
  _state.rp.verts += sizeof(base) / sizeof(base[0]);
  // glEnable (GL_FRAMEBUFFER_SRGB);
#endif

  glBindFramebuffer(GL_FRAMEBUFFER, _state.rp.fbos[SG_FBO]);
  glViewport(0, 0, _state.width, _state.height);
  glClearColor(0, 0, 0, 1);
  glClearDepth(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(_state.rp.program);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_GEQUAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUniform2f(_state.rp.uscreen, _state.width, _state.height);
  glBindVertexArray(_state.rp.vao);
  glBindBuffer(GL_ARRAY_BUFFER, _state.rp.vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SGvertex) * _state.rp.verts,
                  _state.rp.vbuf);

  glDrawArrays(GL_TRIANGLES, 0, _state.rp.verts);

  // FINAL BLITTING
  float x0, x1, y0, y1;
  x0 = -1, x1 = 1, y0 = -1, y1 = 1;
  if (_state.aspect > 1.f) {
    x0 /= _state.aspect;
    x1 /= _state.aspect;
  } else {
    y0 *= _state.aspect;
    y1 *= _state.aspect;
  }

  // I have no clue
  float const u = ((float)_state.width) / SG_MAX_MONWIDTH / 1.016;
  float const v = ((float)_state.height) / SG_MAX_MONHEIGHT / 1.026;

  struct {
    float p[2];
    float uv[2];
  } verts[] = {{{x0, y0}, {0, 0}}, {{x1, y0}, {u, 0}}, {{x1, y1}, {u, v}},
               {{x0, y0}, {0, 0}}, {{x1, y1}, {u, v}}, {{x0, y1}, {0, v}}};

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, _state.winw, _state.winh);
  // Clear screen framebuffer
  glClearColor(0.1, 0.1, 0.1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(_state.rp.blit);
  glDisable(GL_DEPTH);
  glDisable(GL_BLEND);
  // Activate and use texture unit 0
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, _state.rp.texs[SG_COLOR]);
  glUniform1i(_state.rp.utex, 0);
  //  Upload the blit quad data
  glBindVertexArray(_state.rp.va2);
  glBindBuffer(GL_ARRAY_BUFFER, _state.rp.vb2);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  // Reset
  _state.rp.verts = 0;
  _state.rp.cd = 0;
  return 0;
}

static void dt(short x, short y, short x1, short y1, short x2, short y2) {
  static SGvertex verts[3];
  unsigned short const cd = _state.rp.cd;
  SGcolor const ccol = _state.rp.ccol;

  verts[0] = (SGvertex){{x, y}, cd, ccol};
  verts[1] = (SGvertex){{x1, y1}, cd, ccol};
  verts[2] = (SGvertex){{x2, y2}, cd, ccol};

  if (_state.rp.verts >= (1 << SG_MAX_VERTS) - 10)
    return;
  memcpy(_state.rp.vbuf + _state.rp.verts, verts, sizeof(verts));
  _state.rp.verts += 3;
}

#define dq(x, y, x1, y1, x2, y2, x3, y3)                                       \
  dt(x, y, x1, y1, x2, y2);                                                    \
  dt(x1, y1, x2, y2, x3, y3)

#define dr(x, y, w, h) dq(x, y, x + w, y, x, y + h, x + w, y + h)
#define dif(x, x1) (x > x1 ? (x - x1) : (x1 - x))

static void dl(short x, short y, short x1, short y1) {
  static SGvertex verts[6];
  if (x != x1) {
    unsigned short const cd = _state.rp.cd;
    SGcolor const ccol = _state.rp.ccol;
    int dx, dy;
    if (dif(y, y1) > dif(x, x1))
      dx = 1, dy = 0;
    else
      dx = 0, dy = 1;
    verts[0] = (SGvertex){{x + dx, y + dy}, cd, ccol};
    verts[1] = (SGvertex){{x, y}, cd, ccol};
    verts[2] = (SGvertex){{x1 + dx, y1 + dy}, cd, ccol};
    verts[3] = (SGvertex){{x, y}, cd, ccol};
    verts[4] = (SGvertex){{x1, y1}, cd, ccol};
    verts[5] = (SGvertex){{x1 + dx, y1 + dy}, cd, ccol};
    if (_state.rp.verts >= (1 << SG_MAX_VERTS) - 10)
      return;
    memcpy(_state.rp.vbuf + _state.rp.verts, verts, sizeof(verts));
    _state.rp.verts += 6;
  } else {
    dr(x, y, 1, y1 - y);
  }
}

static int l_setColor(lua_State *L) {
  int t = lua_gettop(L);
  if (t < 3)
    return lua_pushnil(L), 1;
  SGcolor c;
  c.a = 0xff;
  for (; t <= 4 && t > 0; t--)
    ((unsigned char *)&c)[t - 1] = lua_tonumber(L, t);
  _state.rp.ccol = c;
  _state.rp.cd++;
  return 0;
}

static int l_drawTriangle(lua_State *L) {
  short v[6];
  char f;
  int t = lua_gettop(L);
  if (t < 6)
    return lua_pushnil(L), 1;
  f = 1;
  if (t == 7)
    f = lua_toboolean(L, 7);
  for (; t >= 1; t--) {
    v[t - 1] = lua_tonumber(L, 6);
  }
  if (f) {
    dt(v[0], v[1], v[2], v[3], v[4], v[5]);
  } else {
    dl(v[0], v[1], v[2], v[3]);
    dl(v[2], v[3], v[4], v[5]);
    dl(v[4], v[5], v[0], v[1]);
  }
  return 0;
}

static int l_drawRectangle(lua_State *L) {
  short x, y, w, h;
  char f;
  int t = lua_gettop(L);
  if (t < 4)
    return lua_pushnil(L), 1;
  x = lua_tonumber(L, 1);
  y = lua_tonumber(L, 2);
  w = lua_tonumber(L, 3);
  h = lua_tonumber(L, 4);
  f = 1;
  if (t >= 5)
    f = lua_toboolean(L, 5);
  if (f) {
    dr(x, y, w, h);
  } else {
    dr(x, y, 1, h);
    dr(x + w - 1, y, 1, h);
    dr(x, y, w, 1);
    dr(x, y + h - 1, w, 1);
  }
  return 0;
}

static int l_drawLine(lua_State *L) {
  short x, y, x1, y1;
  int t = lua_gettop(L);
  if (t < 4)
    return lua_pushnil(L), 1;
  x = lua_tonumber(L, 1);
  y = lua_tonumber(L, 2);
  x1 = lua_tonumber(L, 3);
  y1 = lua_tonumber(L, 4);
  dl(x, y, x1, y1);
  return 0;
}

static float const pi2 = 6.283185f;

static int sgDrawStr(char const *str, float _x, float _y, float size);

static int l_drawArc(lua_State *L) {
  float x, y, o, i, of, a, s, d;
  int t = lua_gettop(L);
  if (t < 3)
    return lua_pushnil(L), 1;
  i = 0;
  of = 0;
  a = pi2;
  x = lua_tonumber(L, 1);
  y = lua_tonumber(L, 2);
  o = lua_tonumber(L, 3);
  float mxy = mini(_state.width, _state.height);
  s = logf(o) / logf(1.1);
  if (t >= 4)
    i = lua_tonumber(L, 4) - 0.2;
  if (t >= 5)
    a = lua_tonumber(L, 5);
  if (t >= 6)
    of = lua_tonumber(L, 6);
  if (t >= 7)
    s = lua_tonumber(L, 7);
  float sa = pi2 / s;
  float ba = of;
  a = clampf(a, -pi2, pi2);
  d = (a >= 0) ? 1 : -1;
  // Math bullshittery
  // x += 0.5;
  // y += 0.5;
  int j;
  float sc, sn, x0, y0, x1, y1;
  sc = ba;
  x1 = cosf(sc), y1 = sinf(sc);
  for (j = 0; j < floorf(a * d / (pi2 / s)); j++) {
    sc = ba + sa * j * d;
    sn = ba + sa * (j + 1) * d;
    x0 = cosf(sc), y0 = sinf(sc), x1 = cosf(sn), y1 = sinf(sn);
    if (x0 < 0) {
      float fact = 1 - 1 / o;
      x0 *= fact;
      x1 *= fact;
    }
    dq((x + x0 * o), (y - y0 * o), (x + x0 * i), (y - y0 * i), (x + x1 * o),
       (y - y1 * o), (x + x1 * i), (y - y1 * i));
  }
  // Draw a quad for the end of the arc exactly
  x0 = x1, y0 = y1;
  sn = a + of;
  x1 = cosf(sn), y1 = sinf(sn);
  dq(x + x0 * o, y - y0 * o, x + x0 * i, y - y0 * i, x + x1 * o, y - y1 * o,
     x + x1 * i, y - y1 * i);
  return 0;
}

/* Hi youtube id like to make an apology... */
static unsigned char hexass[] =
    "$\x82\x01 Z\x00\x03 UU\x03 <\x9e\x03 R\xa5\x03 *\xab\x03 $\x00\x01 "
    ")\"\x03 \"J\x03 \x0A\xA8\x03 \x05\xD0\x03 \x00\x12\x01 \x01\xC0\x03 "
    "\x00\x02\x01 \x12\xA4\x03 +j\x03 ,\x97\x03 b\xa7\x03 b\x8e\x03 )\xd2\x03 "
    "\x79\x8E\x03 )\xaa\x03 r\x92\x03 *\xaa\x03 *\xca\x03 \x04\x10\x01 "
    "\x04\x12\x01 \x05\x10\x03 \x0e\x38\x03 \x04P\x03 \"\x82\x03 \xff\xff\x03 "
    "\x2B\xED\x03 \x6B\xAE\x03 \x39\x23\x03 \x6B\x6E\x03 \x79\xA7\x03 "
    "\x79\xA4\x03 \x39\x2B\x03 \x5B\xED\x03 \x74\x97\x03 \x32\x6A\x03 "
    "\x4B\xAD\x03 \x49\x27\x03 \x5F\x6D\x03 \x7B\x6D\x03 \x7B\x6F\x03 "
    "\x6B\xA4\x03 \x2B\x59\x03 \x6B\xAD\x03 \x38\x8E\x03 \x74\x92\x03 "
    "\x5B\x6A\x03 \x5B\x52\x03 \x5B\x7D\x03 \x5A\xAD\x03 \x5A\x92\x03 "
    "\x72\xA7\x03 \x69\x26\x03 \x48\x89\x03 \x32\x4B\x03 \x2A\x00\x03 "
    "\x00\x07\x03 \x00\x00\x00 \x35\x93\x03 \x24\x92\x01 \x64\xD6\x03 "
    "\x0C\x98\x03";

#define toupper(c) (c >= 'a' ? c - 32 : c)

static int sgDrawStr(char const *str, float _x, float _y, float size) {
  unsigned int i;
  int ii;
  if (!str)
    return -1;
  unsigned int l = strlen(str);
  if (l < 1)
    return -1;

  float rx = _x;
  for (i = 0; i < l; ++i) {
    int o = toupper(str[i]);
    if (o >= 0x7b && o <= 0x7e)
      o -= 26;
    o -= 32;
    if (o < 0 || o > 69) {
      continue;
    }
    if (o == 0) {
      rx += 4.f;
      continue;
    }
    o -= 1;
    int hex = hexass[o * 4] << 8 | hexass[o * 4 + 1];
    char s = hexass[o * 4 + 2];
    rx = rx - ((3 - s) / 2.f) * size;

    for (ii = 14; ii >= 0; --ii) {
      char bit = (hex >> ii) & 0b1;
      int p = 14 - ii;
      char x = (p % 3);
      char y = (p / 3);
      if (bit) {
        float __x = (float)rx + (float)x * size;
        float __y = (float)_y + (float)y * size;
        dr(__x, __y, size, size);
      }
    }
    rx += 4.f * size - ((3 - s) / 2.f) * size;
  }
  return 1;
}

static int l_drawText(lua_State *L) {
  int x, y, scale;
  char const *str;
  int t = lua_gettop(L);
  if (t < 3)
    return lua_pushnil(L), 1;
  if (lua_type(L, 3) != LUA_TSTRING)
    return lua_pushstring(L, "expected a string"), lua_error(L), 1;
  scale = 1;
  x = lua_tonumber(L, 1);
  y = lua_tonumber(L, 2);
  str = lua_tostring(L, 3);
  if (t == 4)
    scale = lua_tonumber(L, 4);
  if (str)
    sgDrawStr(str, x, y, scale);
  return 0;
}

static luaL_Reg const libfuncs[] = {{"setColor", l_setColor},
                                    {"drawTriangle", l_drawTriangle},
                                    {"drawRectangle", l_drawRectangle},
                                    {"drawLine", l_drawLine},
                                    {"drawCircle", l_drawArc},
                                    {"drawText", l_drawText},
                                    {NULL, NULL}};

int sgRenderOpenLibs(lua_State *L) {
  luaL_setfuncs(L, libfuncs, 0);
  return 0;
}
