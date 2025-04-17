#include "sgrender.h"
#include "minilua.h"

#include "sgshader.h"
#include "../build/main_vert.h"
#include "../build/main_frag.h"

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

int sgInitRenderPipe (SGstate *sgs) {
  uint32_t vShader =
      sgCompileShader (GL_VERTEX_SHADER, (char const *)src_shaders_main_vert,
                       src_shaders_main_vert_len);
  if (!vShader)
    return fprintf (stderr, "Vertex shader compile fail\n"), 3;

  uint32_t fShader =
      sgCompileShader (GL_FRAGMENT_SHADER, (char const *)src_shaders_main_frag,
                       src_shaders_main_frag_len);
  if (!fShader)
    return fprintf (stderr, "Fragment shader compile fail\n"), 3;

  glEnable (GL_DEPTH_TEST);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_BLEND);
}