#version 460 core

out vec4 FragColor;

in vec2           UV;
uniform sampler2D screen;

vec3 v3pow (vec3 v, float p) {
  return vec3 (pow (v.r, p), pow (v.g, p), pow (v.b, p));
}

void main() {
  FragColor = texture (screen, UV);

  FragColor = vec4 (pow (FragColor.rgb, vec3 (1.0)), 1.0);
}
