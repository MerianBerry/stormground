#version 330 core

out vec2 UV;

layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vUV;

void main() {
  UV          = vUV;
  gl_Position = vec4 (vPos, 1.0, 1.0);
}