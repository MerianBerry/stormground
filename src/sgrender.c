#include "sgrender.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "minilua.h"
#include "sgapi.h"
#include "sgshader.h"
#include "sgimage.h"
#include "shaders/main_vert.h"
#include "shaders/main_frag.h"

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

static const SGvertex base[] = {
    {.p = {0, 0},   0, .c = {255, 0, 0, 255}},
    {.p = {96, 0},  0, .c = {255, 0, 0, 255}},
    {.p = {0, 96},  0, .c = {255, 0, 0, 255}},
    {.p = {0, 0},   1, .c = {0, 255, 0, 128}},
    {.p = {96, 0},  1, .c = {0, 255, 0, 128}},
    {.p = {96, 96}, 1, .c = {0, 255, 0, 128}},
    {.p = {36, 0},  2, .c = {0, 0, 255, 32} },
    {.p = {36, 96}, 2, .c = {0, 0, 255, 32} },
    {.p = {96, 96}, 2, .c = {0, 0, 255, 32} },
};

#define SG_DEPTH 0
#define SG_COLOR 1
#define SG_DCOPY 2
#define SG_CCOPY 3

#define SG_FBO   0
#define SG_FCOPY 1

int sgInitRenderPipe (SGstate *sgs) {
  unsigned vbo, vao, fbo, fbocopy;
  uint32_t vShader = sgCompileShader (
      GL_VERTEX_SHADER, (char const *)shaders_main_vert, shaders_main_vert_len);
  if (!vShader)
    return fprintf (stderr, "Vertex shader compile fail\n"), 3;

  uint32_t fShader =
      sgCompileShader (GL_FRAGMENT_SHADER, (char const *)shaders_main_frag,
                       shaders_main_frag_len);
  if (!fShader)
    return fprintf (stderr, "Fragment shader compile fail\n"), 3;

  unsigned shaders[] = {vShader, fShader};
  unsigned prog =
      sgLinkShaderProgram (shaders, sizeof (shaders) / sizeof (shaders[0]));
  if (!prog)
    return fprintf (stderr, "Failed to link shader program.\n"), 4;
  glDeleteShader (vShader);
  glDeleteShader (fShader);

  sgs->rp.udepth  = glGetUniformLocation (prog, "depth");
  sgs->rp.uscreen = glGetUniformLocation (prog, "screen");

  unsigned texs[4];
  glGenTextures (4, texs);
  glBindTexture (GL_TEXTURE_2D, texs[SG_DEPTH]);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SG_MAX_MONWIDTH,
                SG_MAX_MONHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture (GL_TEXTURE_2D, texs[SG_COLOR]);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, SG_MAX_MONWIDTH, SG_MAX_MONHEIGHT, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned fbos[2];
  glGenFramebuffers (2, fbos);

  glBindFramebuffer (GL_FRAMEBUFFER, fbos[SG_FBO]);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                          texs[SG_DEPTH], 0);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          texs[SG_COLOR], 0);

  if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return fprintf (stderr, "Framebuffers are not complete.\n"), 4;

  /*glBindFramebuffer (GL_FRAMEBUFFER, fbos[SG_FCOPY]);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                          texs[SG_DCOPY], 0);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          texs[SG_CCOPY], 0);

  if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return fprintf (stderr, "Framebuffers are not complete.\n"), 4;*/

  int const n   = 1 << SG_MAX_VERTS;
  SGvertex *buf = malloc (sizeof (SGvertex) * n);
  if (!buf) {
    fprintf (stderr, "Out of memory\n");
    // Just exit here. There is no recovering.
    exit (1);
  }
  sgs->rp.vbuf = buf;
  memcpy (buf, base, sizeof (base));
  sgs->rp.verts += sizeof (base) / sizeof (base[0]);

  glCreateVertexArrays (1, &vao);
  glCreateBuffers (1, &vbo);

  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof (SGvertex) * n, buf, GL_DYNAMIC_DRAW);

  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (0, 2, GL_SHORT, GL_FALSE, sizeof (SGvertex), 0);

  glEnableVertexAttribArray (1);
  glVertexAttribPointer (1, 1, GL_UNSIGNED_SHORT, GL_TRUE, sizeof (SGvertex),
                         (void *)4);

  glEnableVertexAttribArray (2);
  glVertexAttribPointer (2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (SGvertex),
                         (void *)6);

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_GEQUAL);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);
  glBindFramebuffer (GL_FRAMEBUFFER, 0);

  // glEnable (GL_FRAMEBUFFER_SRGB);

  sgs->rp.npeels = 6;

  sgs->rp.vbo     = vbo;
  sgs->rp.vao     = vao;
  sgs->rp.program = prog;
  memcpy (sgs->rp.fbos, fbos, sizeof (fbos));
  memcpy (sgs->rp.texs, texs, sizeof (texs));
  sgs->rp.cd = 0;
  return 0;
}

int sgDrawRenderPipe (SGstate *sgs, int w, int h) {
  // memcpy (sgs->rp.vbuf, base, sizeof (base));
  // sgs->rp.verts += sizeof (base) / sizeof (base[0]);
  //  glEnable (GL_FRAMEBUFFER_SRGB);

  glBindFramebuffer (GL_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glViewport (0, 0, sgs->width, sgs->height);
  glClearColor (0, 0, 0, 1);
  glClearDepth (0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram (sgs->rp.program);

  // glActiveTexture (GL_TEXTURE0 + 0); // Bind depth to unit 0
  // glBindTexture (GL_TEXTURE_2D, sgs->rp.texs[SG_DCOPY]);

  glUniform1i (sgs->rp.udepth, 0); // Depth bound to unit 0
  glUniform2f (sgs->rp.uscreen, sgs->width, sgs->height);
  glBindBuffer (GL_ARRAY_BUFFER, sgs->rp.vbo);
  glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (SGvertex) * sgs->rp.verts,
                   sgs->rp.vbuf);

  glBindVertexArray (sgs->rp.vao);

  glDrawArrays (GL_TRIANGLES, 0, sgs->rp.verts);

  glBindFramebuffer (GL_READ_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);
  // Clear screen framebuffer
  glClearColor (0, 0, 0, 1);
  glClear (GL_COLOR_BUFFER_BIT);

  float x0, x1, y0, y1;
  x0 = -1, x1 = 1, y0 = -1, y1 = 1;
  if (sgs->aspect > 1.f) {
    x0 /= sgs->aspect;
    x1 /= sgs->aspect;
  } else {
    y0 *= sgs->aspect;
    y1 *= sgs->aspect;
  }
  x0 = (x0 + 1.f) / 2 * w;
  x1 = (x1 + 1.f) / 2 * w;
  y0 = (y0 + 1.f) / 2 * h;
  y1 = (y1 + 1.f) / 2 * h;

  // Copy the virtual screen to the actual screen
  glViewport (0, 0, w, h);
  glBlitFramebuffer (0, 0, sgs->width, sgs->height, x0, y0, x1, y1,
                     GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
  sgs->rp.verts = 0;
  sgs->rp.cd    = 0;
  return 0;
}

static void dr (SGstate *sg, short x, short y, short w, short h) {
  unsigned short const cd      = sg->rp.cd;
  const SGcolor        ccol    = sg->rp.ccol;
  SGvertex             verts[] = {
                  {{x, y},         cd, ccol},
                  {{x + w, y},     cd, ccol},
                  {{x, y + h},     cd, ccol},
                  {{x + w, y},     cd, ccol},
                  {{x + w, y + h}, cd, ccol},
                  {{x, y + h},     cd, ccol},
  };
  if (sg->rp.verts >= 0xfff9)
    return;
  memcpy (sg->rp.vbuf + sg->rp.verts, verts, sizeof (verts));
  sg->rp.verts += 6;
}

static int l_setColor (lua_State *L) {
  CommonAPIHeader (L);
  if (!sgs)
    return lua_pushnil (L), 1;
  int t = lua_gettop (L);
  if (t < 3)
    return lua_pushnil (L), 1;
  SGcolor c;
  c.a = 0xff;
  for (; t <= 4 && t > 0; t--)
    ((unsigned char *)&c)[t - 1] = lua_tonumber (L, t);
  sgs->rp.ccol = c;
  sgs->rp.cd++;
  return 0;
}

static int l_drawRectangle (lua_State *L) {
  short x, y, w, h;
  CommonAPIHeader (L);
  if (!sgs)
    return lua_pushnil (L), 1;
  int t = lua_gettop (L);
  if (t < 4)
    return lua_pushnil (L), 1;
  x = lua_tonumber (L, 1);
  y = lua_tonumber (L, 2);
  w = lua_tonumber (L, 3);
  h = lua_tonumber (L, 4);
  if (!lua_toboolean (L, 5))
    dr (sgs, x, y, w, h);
  else {
    dr (sgs, x, y, 1, h);
    dr (sgs, x + w - 1, y, 1, h);
    dr (sgs, x, y, w, 1);
    dr (sgs, x, y + h - 1, w, 1);
  }
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

static int sgDrawStr (SGstate *sg, char const *str, float _x, float _y,
                      float size) {
  unsigned int i;
  int          ii;
  if (!str)
    return -1;
  unsigned int l = strlen (str);
  if (l < 1)
    return -1;

  float rx = _x;
  for (i = 0; i < l; ++i) {
    int o = toupper (str[i]);
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
    int  hex = hexass[o * 4] << 8 | hexass[o * 4 + 1];
    char s   = hexass[o * 4 + 2];
    rx       = rx - ((3 - s) / 2.f) * size;

    for (ii = 14; ii >= 0; --ii) {
      char bit = (hex >> ii) & 0b1;
      int  p   = 14 - ii;
      char x   = (p % 3);
      char y   = (p / 3);
      if (bit) {
        float __x = (float)rx + (float)x * size;
        float __y = (float)_y + (float)y * size;
        dr (sg, __x, __y, size, size);
      }
    }
    rx += 4.f * size - ((3 - s) / 2.f) * size;
  }
  return 1;
}

static int l_drawText (lua_State *L) {
  int         x, y, scale;
  char const *str;
  CommonAPIHeader (L);
  int t = lua_gettop (L);
  if (t < 3)
    return lua_pushnil (L), 1;
  if (lua_type (L, 3) != LUA_TSTRING)
    return lua_pushstring (L, "expected a string"), lua_error (L), 1;
  scale = 1;
  x     = lua_tonumber (L, 1);
  y     = lua_tonumber (L, 2);
  str   = lua_tostring (L, 3);
  if (t == 4)
    scale = lua_tonumber (L, 4);
  if (str)
    sgDrawStr (sgs, str, x, y, scale);
  return 0;
}

static const luaL_Reg libfuncs[] = {
    {"setColor",      l_setColor     },
    {"drawRectangle", l_drawRectangle},
    {"drawText",      l_drawText     },
    {NULL,            NULL           }
};

int sgRenderOpenLibs (lua_State *L) {
  luaL_setfuncs (L, libfuncs, 0);
  return 0;
}
