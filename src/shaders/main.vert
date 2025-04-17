#version 410 core

out vec3 vPos;
out vec4 col;

in vec3 aPos;
in vec4 aCol;

uniform vec2 screen;

void main() {
  vec2 pos = aPos.xy;
  pos.x /= screen.x;
  pos.y /= screen.y;
  vPos        = vec3 (pos, aPos.z);
  col         = aCol;
  gl_Position = vec4 (vPos, 1.0);
}
