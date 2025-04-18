#version 330 core

out vec3 vPos;
out vec4 col;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

uniform vec2 screen;

void main() {
  vec2 pos = aPos.xy;
  pos.xy -= screen.xy / 2;
  pos /= screen;
  pos *= 2;
  pos.y *= -1;
  vec3 tcol = vec3 (aCol.r, aCol.g, aCol.b);

  vPos        = vec3 (pos.x, pos.y, aPos.z);
  col         = vec4 (tcol, aCol.a);
  gl_Position = vec4 (pos.x, pos.y, aPos.z, 1.0);
}
