#pragma once

#include "sg.h"

enum {
  SG_NOHOLD = 0,
  SG_PRESS,
  SG_HOLD,
  SG_RELEASE,
};

void sgSetCallbackState(SGstate *state);

void sgFramebufSizeCallback(GLFWwindow *win, int width, int height);

void sgMouseButtonCallback(GLFWwindow *win, int button, int action, int mods);

void sgKeyCallback(GLFWwindow *win, int key, int scancode, int action, int mods);

void sgScrollCallback(GLFWwindow *win, double x, double y);

/* void sgJoystickCallback(int jid, int event); */

int sgNumActiveGamepads();

void sgAdvanceInputs();