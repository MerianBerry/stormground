#include "sg.h"
#ifdef _WIN32
#include <dwmapi.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#endif

#include <SDL3/SDL_init.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sgapi.h"
#include "sginput.h"
#include "sgrender.h"

#include "minilua.h"

struct SGstate _state;

static int W = 1280;
static int H = 720;

static int translate_keycode(SDL_Keycode key) {
  // If a normal keycode
  if (!(key & 0x60000000))
    return key;
  switch (key) {
  case SDLK_LSHIFT:
    return SGK_LSHIFT;
  case SDLK_RSHIFT:
    return SGK_RSHIFT;
  case SDLK_LCTRL:
    return SGK_LCTRL;
  case SDLK_RCTRL:
    return SGK_RCTRL;
  case SDLK_LALT:
    return SGK_LALT;
  case SDLK_RALT:
    return SGK_RALT;
  case SDLK_LEFTBRACKET:
    return SGK_LEFTBRACKET;
  case SDLK_RIGHTBRACKET:
    return SGK_RIGHTBRACKET;
  case SDLK_SPACE:
    return SGK_SPACE;
  case SDLK_BACKSPACE:
    return SGK_BACKSPACE;
  case SDLK_TAB:
    return SGK_TAB;
  case SDLK_RETURN:
    return SGK_RETURN;
  case SDLK_MINUS:
    return SGK_MINUS;
  case SDLK_EQUALS:
    return SGK_EQUALS;
  case SDLK_UP:
    return SGK_UP;
  case SDLK_DOWN:
    return SGK_DOWN;
  case SDLK_LEFT:
    return SGK_LEFT;
  case SDLK_RIGHT:
    return SGK_RIGHT;
  case SDLK_COMMA:
    return SGK_COMMA;
  case SDLK_PERIOD:
    return SGK_PERIOD;
  case SDLK_ESCAPE:
    return SGK_ESCAPE;
  case SDLK_SLASH:
    return SGK_SLASH;
  case SDLK_BACKSLASH:
    return SGK_BACKSLASH;
  case SDLK_SEMICOLON:
    return SGK_SEMICOLON;
  case SDLK_DELETE:
    return SGK_DELETE;
  case SDLK_PAGEUP:
    return SGK_PAGEUP;
  case SDLK_PAGEDOWN:
    return SGK_PAGEDOWN;
  case SDLK_HOME:
    return SGK_HOME;
  case SDLK_END:
    return SGK_END;
  case SDLK_INSERT:
    return SGK_INSERT;
  default:
    return 0;
  }
}

static int handle_event(SDL_Event *e) {
  switch (e->type) {
  case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
    _state.runstate = SG_RUNSTATE_STOP;
    return 1;
  case SDL_EVENT_WINDOW_RESIZED:
    _state.winw = e->window.data1;
    _state.winh = e->window.data2;
    glViewport(0, 0, _state.winw, _state.winh);
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
  case SDL_EVENT_MOUSE_BUTTON_UP:
    _state.buttons[e->button.button] =
        e->type == SDL_EVENT_MOUSE_BUTTON_DOWN ? SG_PRESS : SG_RELEASE;
    break;
  case SDL_EVENT_MOUSE_MOTION:
    _state.usage = SG_USAGE_MANDK;
    _state.realCurX = e->motion.x;
    _state.realCurY = e->motion.y;
    break;
  case SDL_EVENT_KEY_DOWN:
  case SDL_EVENT_KEY_UP:
    if (e->type == SDL_EVENT_KEY_DOWN && e->key.repeat)
      _state.keys[translate_keycode(e->key.key)] = SG_REPEAT;
    else
      _state.keys[translate_keycode(e->key.key)] =
          e->type == SDL_EVENT_KEY_DOWN ? SG_PRESS : SG_RELEASE;
    break;
  case SDL_EVENT_MOUSE_WHEEL:
    _state.scrollx = e->wheel.x;
    _state.scrolly = e->wheel.y;
    break;
  }
  return 0;
}

int main(int argc, char **argv) {
  scl_resetclock();

  int r = 0;
  memset(&_state, 0, sizeof(_state));
  _state.mappings = scl_htabnew();
  _state.bmaps = scl_htabnew();
  _state.tfps = 60.f;

  _state.width = 96;
  _state.height = 96;

  if ((r = sgRunCli(argc, argv)) || _state.runstate) {
    return r;
  }

  if (!_state.name) {
    _state.name = (char *)scl_strcopy("Stormground " SG_VERNAME);
  }

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    fprintf(stderr, "Failed to init SDL\n");
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  _state.win = SDL_CreateWindow(_state.name, W, H,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!_state.win) {
    fprintf(stderr, "Failed to init SDL window\n");
    return 1;
  }

#if defined(_WIN32) && defined(GLFW_EXPOSE_NATIVE_WIN32)
#include "resources/rc.h"
  HWND hwnd = glfwGetWin32Window(_state.win);
  BOOL dark_mode = 1;
  DwmSetWindowAttribute(hwnd, 20, &dark_mode, sizeof(dark_mode));
  HICON hi =
      (HICON)LoadImageW(GetModuleHandle(NULL), MAKEINTRESOURCEW(IDI_ICON),
                        IMAGE_ICON, 180, 180, 0);
  // fprintf (stderr, "%p\n", hi);
  if (hi) {
    ICONINFO hiinfo;
    GetIconInfo(hi, &hiinfo);
    HBITMAP hbit = hiinfo.hbmColor;
    // fprintf (stderr, "%p\n", hbit);
    BITMAP bit;
    GetObject(hbit, sizeof(bit), (LPVOID)&bit);
    // fprintf (stderr, "%p, %li %li\n", bit.bmBits, bit.bmWidth, bit.bmHeight);
    if (bit.bmWidth * bit.bmHeight > 0) {
      GLFWimage image;
      unsigned char *copy =
          (unsigned char *)malloc(bit.bmWidth * bit.bmHeight * 4);
      GetBitmapBits(hbit, bit.bmWidth * bit.bmHeight * 4, copy);
      image.pixels = copy;
      image.width = bit.bmWidth;
      image.height = bit.bmHeight;
      glfwSetWindowIcon(_state.win, 1, &image);
    }
  }
#endif

  _state.ctx = SDL_GL_CreateContext(_state.win);
  // SDL_GL_MakeCurrent (_state.win, _state.ctx);
  // 1: vsync, 0: instant
  SDL_GL_SetSwapInterval(0);

  /*
  if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)) {
    fprintf (stderr, "Failed to load OpenGL\n");
    glfwTerminate();
    return 2;
  }*/

  glViewport(0, 0, W, H);

  if ((r = sgInitRenderPipe()))
    return r;

  lua_State *L = sgNewScript();
  if (!scl_exists("main.lua"))
    return fprintf(stderr, "failed to open main.lua\n"), 1;
  if (luaL_dofile(L, "main.lua")) {
    return fprintf(stderr, "script error: %s\n", lua_tostring(L, -1)), 1;
  }

  double cputime = 0.0;
  double luatime = 0.0;
  float delta = 0.0;
  size_t frame = 0;
  double fps = 0.0;
  while (!_state.runstate) {
    double ls = scl_clock();

    sgAdvanceInputs();
    SDL_Event e;
    while (SDL_PollEvent(&e))
      if (handle_event(&e))
        goto endloop;

    ++frame;

    // Fallback for an invalid frame
    if (!_state.winw) {
      SDL_GetWindowSize(_state.win, &_state.winw, &_state.winh);
      glViewport(0, 0, _state.winw, _state.winh);
    }

    W = _state.winw;
    H = _state.winh;
    float aspect1 = (float)W / (float)H;
    float aspect2 = (float)_state.width / (float)_state.height;
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
    } else {
      fw = W;
      fh = H;
      fx = 0;
      fy = 0;
    }
    fx2 = (_state.realCurX - fx) / fw * _state.width;
    fy2 = (_state.realCurY - fy) / fh * _state.height;
    fx2 = floorf((fx2 < 0) ? fx2 - 1.f : fx2);
    fy2 = floorf((fy2 < 0) ? fy2 - 1.f : fy2);
    _state.curx = fx2;
    _state.cury = fy2;
    _state.aspect = daspect;
    double gputims[180];
    int i;
    /*if (_state.gpads[1].connected &&
        _state.gpads[1].buttons[GLFW_GAMEPAD_BUTTON_A] == SG_HOLD) {
      notef ("Pressed A! %.3f\n",
             _state.gpads[1].gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
    }*/
    double lls = scl_clock();
    lua_getglobal(L, "onTick");
    if (lua_pcall(L, 0, 0, 0)) {
      return fprintf(stderr, "script error: %s\n", lua_tostring(L, -1)), 5;
    }
    luatime = luatime * 0.98 + ((scl_clock() - lls) * 1000.0) * 0.02;

    double fs = scl_clock();
    sgDrawRenderPipe();
    gputims[frame % 120] = (scl_clock() - fs) * 1000.0;
    SDL_GL_SwapWindow(_state.win);

    // cputime = (scl_clock() - ls) * 1000.0;
    double cur = scl_clock();
    double _t = (cur - ls) * 1000.0;
    if (_t < 1000.0 / _state.tfps)
      scl_waitms(1000.0 / _state.tfps - _t);
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
    _state.time += _t / 1000.0;
    _state.delta = delta;
  }
endloop:

  // glDeleteVertexArrays (1, &VAO);

  free((void *)_state.name);

  SDL_GL_DestroyContext(_state.ctx);
  SDL_DestroyWindow(_state.win);
  SDL_Quit();

  return 0;
}
