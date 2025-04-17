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
    {
     {0, 0, 0},
     {255, 255, 255, 255},
     },
    {
     {20, 0, 0},
     {255, 255, 255, 255},
     },
    {
     {0, 20, 0},
     {255, 255, 255, 255},
     }
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
  sgs->rp.verts += 3;

  glCreateVertexArrays (1, &vao);
  glCreateBuffers (1, &vbo);

  glNamedBufferData (vbo, sizeof (SGvertex) * n, buf, GL_STATIC_DRAW);

  glBindVertexArray (vao);

  glVertexAttribPointer (0, 3, GL_SHORT, GL_FALSE, sizeof (SGvertex), 0);
  glEnableVertexArrayAttrib (vao, 0);

  glVertexAttribPointer (1, 4, GL_BYTE, GL_FALSE, sizeof (SGvertex), (void *)6);
  glEnableVertexArrayAttrib (vao, 1);
  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_BLEND);

  sgs->rp.npeels = 4;

  sgs->rp.vbo     = vbo;
  sgs->rp.vao     = vao;
  sgs->rp.program = prog;
  memcpy (sgs->rp.fbos, fbos, sizeof (fbos));
  memcpy (sgs->rp.texs, texs, sizeof (texs));
  return 0;
}

int sgDrawRenderPipe (SGstate *sgs, int w, int h) {
  glViewport (0, 0, sgs->width, sgs->height);

  glBindFramebuffer (GL_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glUseProgram (sgs->rp.program);
  glClearColor (0, 0, 0, 0);
  glClearDepth (1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindVertexArray (sgs->rp.vao);
  glBindBuffer (GL_ARRAY_BUFFER, sgs->rp.vbo);

  glActiveTexture (GL_TEXTURE0 + 0); // Bind depth to unit 0
  glBindTexture (GL_TEXTURE_2D, sgs->rp.texs[SG_DCOPY]);

  glUniform1i (sgs->rp.udepth, 0); // Depth bound to unit 0
  glUniform2f (sgs->rp.uscreen, (float)w, (float)h);

  glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (SGvertex) * sgs->rp.verts,
                   sgs->rp.vbuf);

  glDrawArrays (GL_TRIANGLES, 0, sgs->rp.verts);
  /*int i;
  for (i = 0; i < sgs->rp.npeels; i++) {
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

  glBindFramebuffer (GL_DRAW_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);
  glBindFramebuffer (GL_READ_FRAMEBUFFER, sgs->rp.fbos[SG_FCOPY]);
  glBlitFramebuffer (0, 0, sgs->width, sgs->height, 0, 0, w, h,
                     GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer (GL_FRAMEBUFFER, sgs->rp.fbos[SG_FBO]);*/
  return 0;
}
