#include "sg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sgshader.h"
#include "sgcli.h"

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


  glfwInit();
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_RESIZABLE, GLFW_FALSE);

  state.win = glfwCreateWindow (W, H, "stormground", NULL, NULL);
  if (!state.win) {
    fprintf (stderr, "Failed to init GLFW window\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent (state.win);
  glfwSwapInterval (0);

  glfwSetWindowUserPointer (state.win, &state);
}