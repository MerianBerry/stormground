#include "sginput.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

SGstate *sgstate;

void sgSetInputState (SGstate *state) { sgstate = state; }

void sgFramebufSizeCallback (GLFWwindow *win, int width, int height) {
  glViewport (0, 0, width, height);
}

void sgMouseButtonCallback (GLFWwindow *win, int button, int action, int mods) {
  int W, H;
  glfwGetWindowSize (win, &W, &H);
  if (action == GLFW_PRESS && sgstate->buttons[button] == SG_NOHOLD ||
      sgstate->buttons[button] == SG_RELEASE) {
    sgstate->buttons[button] = SG_PRESS;
  } else if (action == GLFW_RELEASE && sgstate->buttons[button] == SG_HOLD ||
             sgstate->buttons[button] == SG_PRESS) {
    sgstate->buttons[button] = SG_RELEASE;
  }
}

void sgCursorPosCallback (GLFWwindow *win, double x, double y) {
  if (x != sgstate->realCurX || y != sgstate->realCurY) {
    sgstate->usage    = SG_USAGE_MANDK;
    sgstate->fakeCurX = x;
    sgstate->fakeCurY = y;
  }
  sgstate->realCurX = x;
  sgstate->realCurY = y;
}

void sgKeyCallback (GLFWwindow *win, int key, int scancode, int action,
                    int mods) {
  int W, H;
  glfwGetWindowSize (win, &W, &H);
  if (action == GLFW_PRESS && sgstate->keys[key] == SG_NOHOLD ||
      sgstate->keys[key] == SG_RELEASE) {
    sgstate->keys[key] = SG_PRESS;
  } else if (action == GLFW_RELEASE && sgstate->keys[key] == SG_HOLD ||
             sgstate->keys[key] == SG_PRESS) {
    sgstate->keys[key] = SG_RELEASE;
  }
}

void sgScrollCallback (GLFWwindow *win, double x, double y) {
  sgstate->scrollx = x;
  sgstate->scrolly = y;
}

#if 0
void sgJoystickCallback (int jid, int event) {
  if (!sgstate)
    return;
  if (event == GLFW_CONNECTED && glfwJoystickIsGamepad (jid)) {
    sgstate->gpads[jid].connected = 1;
    sgstate->gpads[jid].id        = jid;
    sgstate->gpads[jid].name      = (char *)glfwGetJoystickName (jid);
    notef ("Connected joystick %s on id %i\n", sgstate->gpads[jid].name, jid);
  } else if (event == GLFW_DISCONNECTED) {
    sgstate->gpads[jid].connected = 0;
    sgstate->gpads[jid].id        = 0;
    notef ("Connected joystick %s on id %i\n", sgstate->gpads[jid].name, jid);
  }
}
#endif

int sgNumActiveGamepads() {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (sgstate->gpads[i].connected)
      ++n;
  }
  return n;
}

int sgRealGamepadID (SGstate *sgs, int fakeID) {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    int activeID = sgs->activeGpads[i];
    if (sgs->gpads[activeID].connected) {
      ++n;
      if (n == fakeID)
        return activeID;
    }
  }
  return -1;
}

char sgMandKInUse (SGstate *sgs) {
  int i = 0;
  for (i = 0; i < GLFW_KEY_LAST + 1; ++i) {
    if (sgs->keys[i] == SG_PRESS) {
      return 1;
    }
  }
  for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; ++i) {
    if (sgs->buttons[i] == SG_PRESS) {
      return 1;
    }
  }
  return 0;
}

char sgGamepadInUse (SGstate *sgs) {
  int i  = 0;
  int ii = 0;
  for (i = 1; i <= SG_GAMEPAD_LAST; ++i) {
    int realid = sgRealGamepadID (sgs, i);
    if (realid < 0)
      continue;
    Gamepad gp = sgs->gpads[i];
    for (ii = 0; ii < GLFW_GAMEPAD_AXIS_LAST + 1; ++ii) {
      if (gp.gstate.axes[ii] > 0.1) {
        return i;
      }
    }
    for (ii = 0; ii < GLFW_GAMEPAD_BUTTON_LAST + 1; ++ii) {
      if (gp.buttons[ii] == SG_PRESS) {
        return i;
      }
    }
  }
  return -1;
}

void sgInsertActiveGamepad (SGstate *sgs, int id) {
  int i = 0;
  for (i = SG_GAMEPAD_LAST; i > 0; --i) {
    sgs->activeGpads[i] = sgs->activeGpads[i - 1];
  }
  sgs->activeGpads[0] = id;
}

int sgCheckCurrentInputMethod (SGstate *sgs) {
  if (sgMandKInUse (sgs)) {
    /* if (sgs->usage == SG_USAGE_GAMEPAD) {
      notef ("Usage: Mouse & Keyboard\n");
    } */
    sgs->usage = SG_USAGE_MANDK;
    return SG_USAGE_MANDK;
  }
  int id = sgGamepadInUse (sgs);
  if (id > -1) {
    /* sgInsertActiveGamepad (sgs, id); */
    /* if (sgs->usage == SG_USAGE_MANDK) {
      notef ("Usage: Gamepad\n");
    } */
    sgs->usage = SG_USAGE_GAMEPAD;
    return SG_USAGE_GAMEPAD;
  }
  return sgs->usage;
}

void sgAdvanceInputs() {
  int i;
  int ii;
  sgCheckCurrentInputMethod (sgstate);
  for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; ++i) {
    if (sgstate->buttons[i] == SG_PRESS)
      sgstate->buttons[i] = SG_HOLD;
    else if (sgstate->buttons[i] == SG_RELEASE)
      sgstate->buttons[i] = SG_NOHOLD;
  }
  for (i = 0; i < GLFW_KEY_LAST + 1; ++i) {
    if (sgstate->keys[i] == SG_PRESS) {
      sgstate->keys[i] = SG_HOLD;
    } else if (sgstate->keys[i] == SG_RELEASE)
      sgstate->keys[i] = SG_NOHOLD;
  }
  sgstate->scrollx = 0;
  sgstate->scrolly = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (glfwJoystickPresent (i) && glfwJoystickIsGamepad (i)) {
      sgstate->gpads[i].connected = 1;
      if (!sgstate->gpads[i].name) {
        sgstate->gpads[i].name = (char *)glfwGetGamepadName (i);
        notef ("Gamepad \"%s\" was connected on id %i\n",
               sgstate->gpads[i].name, i);
        sgInsertActiveGamepad (sgstate, i);
      }
      glfwGetGamepadState (i, &sgstate->gpads[i].gstate);
      for (ii = 0; ii < GLFW_GAMEPAD_BUTTON_LAST + 1; ++ii) {
        char  action   = sgstate->gpads[i].gstate.buttons[ii];
        char  oldstate = sgstate->gpads[i].buttons[ii];
        char *sgbutton = (char *)sgstate->gpads[i].buttons + ii;
        if (oldstate == SG_PRESS) {
          (*sgbutton) = SG_HOLD;
        } else if (oldstate == SG_RELEASE) {
          (*sgbutton) = SG_NOHOLD;
        }
        if (action == GLFW_PRESS &&
            (oldstate == SG_NOHOLD || oldstate == SG_RELEASE)) {
          (*sgbutton) = SG_PRESS;
        } else if (action == GLFW_RELEASE &&
                   (oldstate == SG_HOLD || oldstate == SG_PRESS)) {
          (*sgbutton) = SG_RELEASE;
        }
      }

    } else {
      sgstate->gpads[i].connected = 0;
      if (sgstate->gpads[i].name) {
        notef ("Gamepad \"%s\" was disconnected on id %i\n",
               sgstate->gpads[i].name, i);
      }

      sgstate->gpads[i].name = NULL;
    }
  }
}
