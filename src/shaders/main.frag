#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 vPos;
in vec2 tPos;
in vec4 col;

void main() {
  FragColor = col;
}
