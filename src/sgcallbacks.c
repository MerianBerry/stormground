#include "sgcallbacks.h"

void sgFramebufSizeCallback (GLFWwindow *win, int width, int height) {
  SGstate *state = glfwGetWindowUserPointer (win);
  glViewport (0, 0, width, height);
}

void sgMouseButtonCallback (GLFWwindow *win, int button, int action, int mods) {
  SGstate *state = glfwGetWindowUserPointer (win);
  int      W, H;
  glfwGetWindowSize (win, &W, &H);
  if (action == GLFW_PRESS && state->buttons[button] == SG_NOHOLD ||
      state->buttons[button] == SG_RELEASE) {
    state->buttons[button] = SG_PRESS;
  } else if (action == GLFW_RELEASE && state->buttons[button] == SG_HOLD ||
             state->buttons[button] == SG_PRESS) {
    state->buttons[button] = SG_RELEASE;
  }
}

void sgKeyCallback (GLFWwindow *win, int key, int scancode, int action,
                    int mods) {
  SGstate *state = glfwGetWindowUserPointer (win);
  int      W, H;
  glfwGetWindowSize (win, &W, &H);
  if (action == GLFW_PRESS && state->keys[key] == SG_NOHOLD ||
      state->keys[key] == SG_RELEASE) {
    state->keys[key] = SG_PRESS;
  } else if (action == GLFW_RELEASE && state->keys[key] == SG_HOLD ||
             state->keys[key] == SG_PRESS) {
    state->keys[key] = SG_RELEASE;
  }
}

void sgScrollCallback (GLFWwindow *win, double x, double y) {
  SGstate *state = glfwGetWindowUserPointer (win);
}

void sgAdvanceInputs (SGstate *state) {
  int i;
  for (i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
    if (state->buttons[i] == SG_PRESS)
      state->buttons[i] = SG_HOLD;
    else if (state->buttons[i] == SG_RELEASE)
      state->buttons[i] = SG_NOHOLD;
  }
  for (i = 0; i < GLFW_KEY_LAST; ++i) {
    if (state->keys[i] == SG_PRESS) {
      state->keys[i] = SG_HOLD;
    } else if (state->keys[i] == SG_RELEASE)
      state->keys[i] = SG_NOHOLD;
  }
}