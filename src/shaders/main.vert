#version 330 core

out vec3 vPos;
out vec2 tPos;
out vec4 col;

layout(location = 0) in vec2 aPos;
layout(location = 1) in float aDepth;
layout(location = 2) in vec4 aCol;

uniform vec2 screen;

void main() {
  vec2 pos = aPos.xy;
  pos.xy -= screen.xy / 2;
  pos /= screen;
  pos *= 2;
  pos.y *= -1;
  vec3 tcol = vec3(aCol.r, aCol.g, aCol.b);

  tPos = aPos.xy / screen.xy;
  tPos.y = 1.0 - tPos.y;
  vPos = vec3(pos.x, pos.y, aDepth);
  col = vec4(tcol, aCol.a);
  gl_Position = vec4(pos.x, pos.y, aDepth, 1.0);
}
