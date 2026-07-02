#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 UV;

uniform sampler2D tex;

void main() {
  vec4 col  = texture (tex, UV).rgba;
  FragColor = vec4 (pow (col.rgb, vec3 (1 / 2.2)) * col.a, 1);
}
