#include "sgrender.h"
#include "minilua.h"

#include <stdlib.h>
#include <string.h>

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
    {.p = {0, 0, 0},   .c = {255, 0, 2, 255}},
    {.p = {96, 0, 0},  .c = {255, 0, 2, 255}},
    {.p = {0, 96, 0},  .c = {255, 0, 2, 255}},
    {.p = {0, 0, 0},   .c = {0, 255, 1, 128}},
    {.p = {96, 0, 0},  .c = {0, 255, 1, 128}},
    {.p = {96, 96, 0}, .c = {0, 255, 1, 128}},
    {.p = {36, 0, 0},  .c = {0, 0, 255, 32} },
    {.p = {36, 96, 0}, .c = {0, 0, 255, 32} },
    {.p = {96, 96, 0}, .c = {0, 0, 255, 32} },
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

  glBindTexture (GL_TEXTURE_2D, texs[SG_DCOPY]);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SG_MAX_MONWIDTH,
                SG_MAX_MONHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture (GL_TEXTURE_2D, texs[SG_CCOPY]);
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

  glBindFramebuffer (GL_FRAMEBUFFER, fbos[SG_FCOPY]);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                          texs[SG_DCOPY], 0);
  glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                          texs[SG_CCOPY], 0);

  if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return fprintf (stderr, "Framebuffers are not complete.\n"), 4;

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
  glVertexAttribPointer (0, 3, GL_SHORT, GL_FALSE, sizeof (SGvertex), 0);

  glEnableVertexAttribArray (1);
  glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (SGvertex),
                         (void *)offsetof (SGvertex, c));

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);
  glBindFramebuffer (GL_FRAMEBUFFER, 0);

  // glEnable (GL_FRAMEBUFFER_SRGB);

  sgs->rp.npeels = 4;

  sgs->rp.vbo     = vbo;
  sgs->rp.vao     = vao;
  sgs->rp.program = prog;
  memcpy (sgs->rp.fbos, fbos, sizeof (fbos));
  memcpy (sgs->rp.texs, texs, sizeof (texs));
  return 0;
}

int sgDrawRenderPipe (SGstate *sgs, int w, int h) {
  glBindFramebuffer (GL_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glViewport (0, 0, sgs->width, sgs->height);
  glClearColor (0, 0, 0, 1);
  glClearDepth (1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram (sgs->rp.program);

  glActiveTexture (GL_TEXTURE0 + 0); // Bind depth to unit 0
  glBindTexture (GL_TEXTURE_2D, sgs->rp.texs[SG_DCOPY]);

  glUniform1i (sgs->rp.udepth, 0); // Depth bound to unit 0
  glUniform2f (sgs->rp.uscreen, sgs->width, sgs->height);
  glBindBuffer (GL_ARRAY_BUFFER, sgs->rp.vbo);
  glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (SGvertex) * sgs->rp.verts,
                   sgs->rp.vbuf);

  glBindVertexArray (sgs->rp.vao);
  int i;
  for (i = 0; i < sgs->rp.npeels; i++) {
    glDrawArrays (GL_TRIANGLES, 0, sgs->rp.verts);
    // Copy the active fbo to the secondary fbo.
    glBindFramebuffer (GL_READ_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
    glBindFramebuffer (GL_DRAW_FRAMEBUFFER, sgs->rp.fbos[SG_FCOPY]);
    glBlitFramebuffer (0, 0, SG_MAX_MONWIDTH, SG_MAX_MONHEIGHT, 0, 0,
                       SG_MAX_MONWIDTH, SG_MAX_MONHEIGHT, GL_DEPTH_BUFFER_BIT,
                       GL_NEAREST);
    glBlitFramebuffer (0, 0, SG_MAX_MONWIDTH, SG_MAX_MONHEIGHT, 0, 0,
                       SG_MAX_MONWIDTH, SG_MAX_MONHEIGHT, GL_COLOR_BUFFER_BIT,
                       GL_NEAREST);
  }
  glBindFramebuffer (GL_READ_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);
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

  glViewport (0, 0, w, h);
  glBlitFramebuffer (0, 0, sgs->width, sgs->height, x0, y0, x1, y1,
                     GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
  return 0;
}
