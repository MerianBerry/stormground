#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 UV;

uniform sampler2D tex;

void main() {
  vec3 col  = texture (tex, UV).rgb;
  FragColor = vec4 (col, 1);
}
