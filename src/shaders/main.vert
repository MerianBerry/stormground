#version 460 core

out vec2 UV;

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 iUV;
uniform float aspect;

float signf (float x) { return (x > 0.0) ? 1.0 : -1.0; }

void main() {
  vec2 pos = aPos;

  if (aspect > 1.0) {
    pos.x = signf (pos.x) / aspect;
  } else if (aspect < 1.0) {
    pos.y = signf (pos.y) * aspect;
  }
  gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
  UV = vec2(iUV.x, 1.0 - iUV.y);
}