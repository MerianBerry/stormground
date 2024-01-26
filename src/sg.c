#include "sg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sgshader.h"
#include "sgcli.h"
#include "sginput.h"
#include "sgapi.h"
#include "sgimage.h"
#include "cJSON/cJSON.h"

binary (main_vert);
binary (main_frag);
binary (main_comp);

static SGstate state;

static int W = 1280;
static int H = 720;

static float vertices[] = {
    1.f,  1.f,  1.f, 1.f, /* top right */
    1.f,  -1.f, 1.f, 0.f, /* bottom right */
    -1.f, -1.f, 0.f, 0.f, /* bottom left */
    -1.f, 1.f,  0.f, 1.f, /* top left */
};
static unsigned int indices[] = {
    /* note that we start from 0! */
    0, 1, 3, /* first Triangle */
    1, 2, 3 /* second Triangle */
};

SSBO* ssboBuf;

struct SSBONOPRIM {
  float time;
  int   primc;
};

static SGprimitive tprim;

typedef struct PackedVert {
  h_vec2 p;
  h_vec3 c;
} PackedVert;

/*long sgPackTriangles (uint32_t VAO, uint32_t VBO) {
  PackedVert* pvv = NULL;

  int pvc = 0;
  int i;
  for (i = 0; i < state.tric; ++i) {
    struct PackedVert v3[3] = {0};
    SGtriangle        t     = state.triv[i];
    float             r     = (float)t.c.r / 255.f;
    float             g     = (float)t.c.g / 255.f;
    float             b     = (float)t.c.b / 255.f;
    v3[0].x                 = t.p1.x;
    v3[0].y                 = t.p1.y;
    v3[1].x                 = t.p2.x;
    v3[1].y                 = t.p2.y;
    v3[2].x                 = t.p3.x;
    v3[2].y                 = t.p3.y;
    printf ("%f\n", v3[0].x);
    int i2;
    for (i2 = 0; i2 < 3; ++i2) {
      v3[i2].r = r;
      v3[i2].g = g;
      v3[i2].b = b;
    }
    pvv = mem_grow (pvv, sizeof (struct PackedVert), pvc, v3, 3);
    pvc += 3;
  }
  // printf ("SUPERBLY FUN %i\n", pvc);
  glBindBuffer (GL_ARRAY_BUFFER, VBO);
  glBufferData (GL_ARRAY_BUFFER, sizeof (struct PackedVert) * pvc, pvv,
                GL_DYNAMIC_DRAW);
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  free (pvv);
  // printf ("BLACKOUT FUN\n");
  return pvc;
}*/

#define funny(name)                                              \
  printf ("case %u: /* " name " */ return GLFW_MOUSE_BUTTON_\n", \
          str_hash (name))

int main (int argc, char** argv) {
  resolve_binary_size (main_vert);
  resolve_binary_size (main_frag);
  resolve_binary_size (main_comp);

#if 0
  funny ("left");
  funny ("right");
  funny ("middle");
  funny ("button1");
  funny ("button2");
  funny ("button3");
  funny ("button4");
  funny ("button5");
  funny ("button6");
  funny ("button7");
  funny ("button8");

#endif
#if 0
  funny ("lshift");
  funny ("rshift");
  funny ("lcontrol");
  funny ("rcontrol");
  funny ("lalt");
  funny ("ralt");
  funny ("lbracket");
  funny ("rbracket");
  funny ("space");
  funny ("backspace");
  funny ("tab");
  funny ("enter");
  funny ("minus");
  funny ("equal");
  funny ("up");
  funny ("down");
  funny ("left");
  funny ("right");
  funny ("comma");
  funny ("period");
  funny ("escape");
  funny ("slash");
  funny ("backslash");
  funny ("semicolon");
  funny ("delete");
  funny ("page up");
  funny ("page down");
  funny ("home");
  funny ("end");
  funny ("insert");



  int ii;
  for (ii = 48; ii <= 57; ++ii) {
    char const s[2] = {(char)ii, '\0'};
    printf ("case %u: /* %c */ return GLFW_KEY_%c;\n", str_hash (s), ii, ii);
    /*uint32_t   hash = str_hash (s);
    printf ("%c = %u\n", (char)ii, hash);*/
  }
#endif

  state = (SGstate){0};

  ssboBuf = malloc (sizeof (struct SSBO));
  if (!ssboBuf) {
    errorf ("Failed to allocate ssbo buffer.\n");
    return 1;
  }
  memset (ssboBuf, 0, sizeof (struct SSBO));

  ssboBuf->primv[0] = tprim;

  state.tfps       = 60.f;
  state.projectDir = (char*)str_cpy (".", npos);
  state.ssbo       = ssboBuf;

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
    errorf ("project json root does not have a child node\n");
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

  sgSetInputState (&state);
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
  glfwSetCursorPosCallback (state.win, sgCursorPosCallback);
  // glfwSetJoystickCallback (sgJoystickCallback);

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

  glNamedBufferData (VBO, sizeof (vertices), vertices, GL_STATIC_DRAW);
  glNamedBufferData (EBO, sizeof (indices), indices, GL_STATIC_DRAW);

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

  sgGenTextures2D (GL_LINEAR, GL_NEAREST, GL_MIRRORED_REPEAT,
                   GL_MIRRORED_REPEAT, GL_RGBA32F, state.width, state.height, 1,
                   &state.mon);
  sgBindTexture (state.mon, GL_READ_WRITE);

  int work_grp_cnt[3];
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

  int work_grp_size[3];
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
  glGetIntegeri_v (GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

  int work_grp_inv;
  glGetIntegerv (GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);

  uint32_t ssbo;
  glGenBuffers (1, &ssbo);
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData (GL_SHADER_STORAGE_BUFFER, sizeof (struct SSBO), ssboBuf,
                GL_DYNAMIC_READ);
  glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 1, ssbo);
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

  SGscript sgscr = {0};
  sgDoFile (&sgscr, &state, "main.lua");

  h_timepoint ls      = timenow();
  double      cputime = 0.0;
  float       delta   = 0.0;
  size_t      frame   = 0;
  double      fps     = 0.0;
  while (1) {
    if (glfwWindowShouldClose (state.win)) {
      state.runstate = SG_RUNSTATE_STOP;
    }
    if (state.runstate == SG_RUNSTATE_STOP)
      break;

    ++frame;

    glClearColor (.1f, .1f, .1f, 1.f);
    glClear (GL_COLOR_BUFFER_BIT);

    glfwGetWindowSize (state.win, &W, &H);
    float aspect1 = (float)W / (float)H;
    float aspect2 = (float)state.width / (float)state.height;
    float daspect = aspect1 / aspect2;
    /* y = -(y - H); */
    float fx, fy, fx2, fy2, fw, fh;
    if (daspect > 1.0) {
      fw = (float)W / daspect;
      fh = H;
      fx = ((float)W - fw) / 2.f;
      fy = 0;
    } else if (daspect < 1.0) {
      fw = W;
      fh = (float)H * daspect;
      fx = 0;
      fy = ((float)H - fh) / 2.f;
    }
    fx2        = (state.fakeCurX - fx) / fw * state.width;
    fy2        = (state.fakeCurY - fy) / fh * state.height;
    fx2        = floorf ((fx2 < 0) ? fx2 - 1.f : fx2);
    fy2        = floorf ((fy2 < 0) ? fy2 - 1.f : fy2);
    state.curx = fx2;
    state.cury = fy2;

    int i;
    /*if (state.gpads[1].connected &&
        state.gpads[1].buttons[GLFW_GAMEPAD_BUTTON_A] == SG_HOLD) {
      notef ("Pressed A! %.3f\n",
             state.gpads[1].gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
    }*/
    if (sgCallGlobal (&sgscr, "onTick")) {
      exit (5);
    }

    ssboBuf->time = state.time / 1000.0;

    glBindBuffer (GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData (
        GL_SHADER_STORAGE_BUFFER, 0,
        sizeof (struct SSBONOPRIM) + sizeof (SGprimitive) * ssboBuf->primc,
        ssboBuf);
    glBindBuffer (GL_SHADER_STORAGE_BUFFER, ssbo);

    glUseProgram (computeProgram);
    glDispatchCompute (state.width / 8, state.height / 4, 1);
    glMemoryBarrier (GL_ALL_BARRIER_BITS);
    glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

    ssboBuf->primc = 0;

    glUseProgram (shaderProgram);
    glBindTextureUnit (0, state.mon.tex);
    glUniform1i (glGetUniformLocation (shaderProgram, "screen"), 0);
    glBindVertexArray (VAO);
    glUniform1f (glGetUniformLocation (shaderProgram, "aspect"), daspect);
    glDrawElements (GL_TRIANGLES, sizeof (indices) / sizeof (indices[0]),
                    GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);


    glfwSwapBuffers (state.win);
    sgAdvanceInputs();
    glfwPollEvents();

    cputime = timeduration (timenow(), ls, milliseconds_e);
    waitms (maxf ((1.0 / (state.tfps * 1.01)) * 1000.0 - cputime, 0));
    double _t = timeduration (timenow(), ls, milliseconds_e);
    fps       = fps * 0.95 + (1.0 / _t * 1000.0) * 0.05;
    if (frame % 180 == 0) {
      /*printf ("x: %lf, y: %lf\n", x, y);
      printf ("fx: %f, fy: %f\n", fx, fy);
      printf ("fx2: %f, fy2: %f\n", fx2, fy2);*/
      /* printf ("FPS: %0.0lf\nCPU time: %0.03lfms\n", fps, cputime); */
    }
    delta = _t;
    state.time += _t / 1000.0;
    state.delta = delta;
    ls          = timenow();
  }


  glDeleteVertexArrays (1, &VAO);

  free ((void*)state.name);
  free ((void*)state.projectFileContent.data);
  free ((void*)state.projectDir);

  glfwDestroyWindow (state.win);
  glfwTerminate();
  free (ssboBuf);

  return 0;
}