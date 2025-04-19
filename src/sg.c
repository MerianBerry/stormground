#include "sg.h"
#ifdef _WIN32
#  include <dwmapi.h>
#  define GLFW_EXPOSE_NATIVE_WIN32
#  include "GLFW/glfw3native.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sginput.h"
#include "sgrender.h"
#include "sgapi.h"

#include "minilua.h"

static SGstate state;

static int W = 1280;
static int H = 720;

int main (int argc, char** argv) {
  scl_resetclock();
  int r          = 0;
  state          = (SGstate){0};
  state.mappings = scl_htabnew();
  state.bmaps    = scl_htabnew();
  state.tfps     = 60.f;

  state.width  = 96;
  state.height = 96;

  if ((r = sgRunCli (&state, argc, argv)) || state.runstate) {
    return r;
  }

  if (!state.name) {
    state.name = (char*)scl_strcopy ("Stormground 1.4");
  }

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

#if defined(_WIN32) && defined(GLFW_EXPOSE_NATIVE_WIN32)
  HWND hwnd      = glfwGetWin32Window (state.win);
  BOOL dark_mode = 1;
  DwmSetWindowAttribute (hwnd, 20, &dark_mode, sizeof (dark_mode));
  HICON hi =
      (HICON)LoadImageW (GetModuleHandle (NULL), MAKEINTRESOURCEW (IDI_ICON),
                         IMAGE_ICON, 180, 180, 0);
  // fprintf (stderr, "%p\n", hi);
  if (hi) {
    ICONINFO hiinfo;
    GetIconInfo (hi, &hiinfo);
    HBITMAP hbit = hiinfo.hbmColor;
    // fprintf (stderr, "%p\n", hbit);
    BITMAP bit;
    GetObject (hbit, sizeof (bit), (LPVOID)&bit);
    // fprintf (stderr, "%p, %li %li\n", bit.bmBits, bit.bmWidth, bit.bmHeight);
    if (bit.bmWidth * bit.bmHeight > 0) {
      GLFWimage      image;
      unsigned char* copy =
          (unsigned char*)malloc (bit.bmWidth * bit.bmHeight * 4);
      GetBitmapBits (hbit, bit.bmWidth * bit.bmHeight * 4, copy);
      image.pixels = copy;
      image.width  = bit.bmWidth;
      image.height = bit.bmHeight;
      glfwSetWindowIcon (state.win, 1, &image);
    }
  }
#endif

  glfwMakeContextCurrent (state.win);
  // 1: vsync, 0: instant
  glfwSwapInterval (0);

  sgSetInputState (&state);
  glfwSetWindowUserPointer (state.win, &state);

  if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)) {
    fprintf (stderr, "Failed to load OpenGL\n");
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

  if ((r = sgInitRenderPipe (&state)))
    return r;

  lua_State* L = sgNewScript (&state);
  if (!scl_exists ("main.lua"))
    return fprintf (stderr, "failed to open main.lua\n"), 1;
  if (luaL_dofile (L, "main.lua")) {
    return fprintf (stderr, "script error: %s\n", lua_tostring (L, -1)), 1;
  }

  double cputime = 0.0;
  double luatime = 0.0;
  float  delta   = 0.0;
  size_t frame   = 0;
  double fps     = 0.0;
  while (1) {
    double ls = scl_clock();
    if (glfwWindowShouldClose (state.win)) {
      state.runstate = SG_RUNSTATE_STOP;
      break;
    }

    sgAdvanceInputs();
    glfwPollEvents();

    ++frame;

    glfwGetWindowSize (state.win, &W, &H);
    float aspect1 = (float)W / (float)H;
    float aspect2 = (float)state.width / (float)state.height;
    float daspect = aspect1 / aspect2;
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
    fx2          = (state.fakeCurX - fx) / fw * state.width;
    fy2          = (state.fakeCurY - fy) / fh * state.height;
    fx2          = floorf ((fx2 < 0) ? fx2 - 1.f : fx2);
    fy2          = floorf ((fy2 < 0) ? fy2 - 1.f : fy2);
    state.curx   = fx2;
    state.cury   = fy2;
    state.aspect = daspect;
    double gputims[180];
    int    i;
    /*if (state.gpads[1].connected &&
        state.gpads[1].buttons[GLFW_GAMEPAD_BUTTON_A] == SG_HOLD) {
      notef ("Pressed A! %.3f\n",
             state.gpads[1].gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
    }*/
    double lls = scl_clock();
    lua_getglobal (L, "onTick");
    if (lua_pcall (L, 0, 0, 0)) {
      return fprintf (stderr, "script error: %s\n", lua_tostring (L, -1)), 5;
    }
    luatime = luatime * 0.98 + ((scl_clock() - lls) * 1000.0) * 0.02;

    double fs = scl_clock();
    sgDrawRenderPipe (&state, W, H);
    gputims[frame % 120] = (scl_clock() - fs) * 1000.0;
    glfwSwapBuffers (state.win);

    // cputime = (scl_clock() - ls) * 1000.0;
    double cur = scl_clock();
    double _t  = (cur - ls) * 1000.0;
    if (_t < 1000.0 / state.tfps)
      scl_waitms (1000.0 / state.tfps - _t);
    _t = (scl_clock() - ls) * 1000.0;

    fps = fps * 0.95 + (1.0 / _t * 1000.0) * 0.05;
#if 0
    if (frame % 120 == 0) {
      double gputime = 0.0;
      for (int i = 0; i < 120; i++)
        gputime += gputims[i];
      gputime /= 120.0;
      printf ("FPS: %0.0lf\nLUA time: %0.03lfms\nGPU time: %0.03lfms\n", fps,
              luatime, gputime);
    }
#endif
    delta = _t;
    state.time += _t / 1000.0;
    state.delta = delta;
  }

  // glDeleteVertexArrays (1, &VAO);

  free ((void*)state.name);

  glfwDestroyWindow (state.win);
  glfwTerminate();

  return 0;
}