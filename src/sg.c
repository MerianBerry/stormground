#include "sg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sgshader.h"
#include "sgcli.h"
#include "sgcallbacks.h"
#include "cJSON/cJSON.h"

binary (main_vert);
binary (main_frag);
binary (main_comp);

SGstate state = {0};

static int W = 1280;
static int H = 720;

int main (int argc, char** argv) {
  resolve_binary_size (main_vert);
  resolve_binary_size (main_frag);
  resolve_binary_size (main_comp);


  float vertices[] = {
      1.f,  1.f,  1.f, 1.f, /* top right */
      1.f,  -1.f, 1.f, 0.f, /* bottom right */
      -1.f, -1.f, 0.f, 0.f, /* bottom left */
      -1.f, 1.f,  0.f, 1.f, /* top left */
  };
  unsigned int indices[] = {
      /* note that we start from 0! */
      0, 1, 3, /* first Triangle */
      1, 2, 3 /* second Triangle */
  };

  state.tfps       = 60.f;
  state.projectDir = (char*)str_cpy (".", npos);

  if (doTheDoThing (&state, argc, argv)) {
    return 1;
  }
  cJSON* projectJSON = cJSON_ParseWithLength (state.projectFileContent.data,
                                              state.projectFileContent.size);
  if (!projectJSON) {
    errorf ("Failed to parse project json!\n\t%s\n", cJSON_GetErrorPtr());
    return 1;
  }
  if (projectJSON->type != cJSON_Object) {
    errorf ("project json root is not an object\n");
    exit (2);
  }
  if (!projectJSON->child) {
    error ("project json root does not have a child node\n");
    exit (2);
  }
  cJSON* itr = projectJSON->child;
  while (itr) {
    if (!strcmp (itr->string, "monitorWidth") && itr->type == cJSON_Number) {
      state.width = itr->valueint;
      if (state.width < 1 || state.width > 1080) {
        errorf (
            "project monitor width is outside acceptable bounds\n\t%i is not "
            "within such bounds\n",
            state.width);
        exit (2);
      }
    } else if (!strcmp (itr->string, "monitorHeight") &&
               itr->type == cJSON_Number) {
      state.height = itr->valueint;
      if (state.height < 1 || state.height > 1080) {
        errorf (
            "project monitor height is outside acceptable bounds\n\t%i is not "
            "within such bounds\n",
            state.height);
        exit (2);
      }
    } else if (!strcmp (itr->string, "name") && itr->type == cJSON_String) {
      state.name = (char*)str_cpy (itr->valuestring, npos);
    }
    itr = itr->next;
  }
  if (!state.width || !state.height) {
    errorf ("Project settings is missing monitor width and height\n");
    exit (2);
  }
  if (!state.name) {
    state.name = (char*)str_cpy ("stormground", npos);
  }

  cJSON_Delete (projectJSON);

  /* char* fpath = io_fullpath ("~/hello/./yes"); */


  glfwInit();
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_RESIZABLE, GLFW_TRUE);

  state.win = glfwCreateWindow (W, H, state.name, NULL, NULL);
  if (!state.win) {
    fprintf (stderr, "Failed to init GLFW window\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent (state.win);
  glfwSwapInterval (0);

  glfwSetWindowUserPointer (state.win, &state);

  if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)) {
    fprintf (stderr, "Failled to load OpenGL\n");
    glfwTerminate();
    return 2;
  }

  glViewport (0, 0, W, H);
  glfwSetFramebufferSizeCallback (state.win, sgFramebufSizeCallback);
  glfwSetKeyCallback (state.win, sgKeyCallback);
  glfwSetScrollCallback (state.win, sgScrollCallback);
  glfwSetMouseButtonCallback (state.win, sgMouseButtonCallback);

  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_BLEND);

  uint32_t vShader =
      sgCompileShader (GL_VERTEX_SHADER, main_vert_start, main_vert_size);
  if (!vShader) {
    errorf ("Vertex shader compile fail\n");
    glfwTerminate();
    exit (3);
  }
  uint32_t fShader =
      sgCompileShader (GL_FRAGMENT_SHADER, main_frag_start, main_frag_size);
  if (!fShader) {
    errorf ("Fragment shader compile fail\n");
    glfwTerminate();
    exit (3);
  }
  uint32_t cShader =
      sgCompileShader (GL_COMPUTE_SHADER, main_comp_start, main_comp_size);
  if (!cShader) {
    errorf ("Compute shader compile fail\n");
    glfwTerminate();
    exit (3);
  }

  uint32_t shaders[] = {vShader, fShader};
  uint32_t shaderProgram =
      sgLinkShaderProgram (shaders, sizeof (shaders) / sizeof (shaders[0]));
  if (!shaderProgram) {
    glfwTerminate();
    exit (4);
  }
  glDeleteShader (vShader);
  glDeleteShader (fShader);

  uint32_t computeProgram = sgLinkShaderProgram (&cShader, 1);
  if (!computeProgram) {
    glfwTerminate();
    exit (4);
  }
  glDeleteShader (cShader);

  unsigned int VBO, VAO, EBO;
  glCreateVertexArrays (1, &VAO);
  glCreateBuffers (1, &VBO);
  glCreateBuffers (1, &EBO);

  glNamedBufferData (VBO, sizeof (vertices), vertices, GL_DYNAMIC_DRAW);
  glNamedBufferData (EBO, sizeof (indices), indices, GL_DYNAMIC_DRAW);

  glEnableVertexArrayAttrib (VAO, 0);
  glVertexArrayAttribBinding (VAO, 0, 0);
  glVertexArrayAttribFormat (VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);

  glEnableVertexArrayAttrib (VAO, 1);
  glVertexArrayAttribBinding (VAO, 1, 0);
  glVertexArrayAttribFormat (VAO, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof (float));

  glVertexArrayVertexBuffer (VAO, 0, VBO, 0, 4 * sizeof (float));
  glVertexArrayElementBuffer (VAO, EBO);

  /* remember: do NOT unbind the EBO while a VAO is active as the bound element
   * buffer object IS stored in the VAO; keep the EBO bound.
   */

  h_timepoint ls      = timenow();
  double      cputime = 0.0;
  float       delta   = 0.0;
  double      time    = 0.0;
  size_t      frame   = 0;
  double      fps     = 0.0;
  while (1) {
    if (glfwWindowShouldClose (state.win)) {
      state.runstate = runstate_stop;
    }
    if (state.runstate == runstate_stop)
      break;

    ++frame;
    glClearColor (.1f, .1f, .1f, 1.f);
    glClear (GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers (state.win);
    sgAdvanceInputs (&state);
    glfwPollEvents();

    cputime = timeduration (timenow(), ls, milliseconds_e);
    waitms (maxf ((1.0 / state.tfps) * 1000.0 - cputime, 0));
    double _t = timeduration (timenow(), ls, milliseconds_e);
    fps       = fps * 0.95 + (1.0 / _t * 1000.0) * 0.05;
    /*if (frame % 180 == 0) {
      printf ("FPS: %0.0lf\nCPU time: %0.03lfms\n", fps, cputime);
    }*/
    delta = _t;
    time += _t;
    ls = timenow();
  }

  glDeleteVertexArrays (1, &VAO);
  glDeleteBuffers (1, &VBO);
  glDeleteBuffers (1, &EBO);

  free ((void*)state.name);
  free ((void*)state.projectFileContent.data);
  free ((void*)state.projectDir);

  glfwDestroyWindow (state.win);
  glfwTerminate();

  return 0;
}