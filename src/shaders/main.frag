#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 vPos;
in vec4 col;

uniform sampler2D depth;

void main() {
  /*if (vPos.z <= texture2D (depth, vPos.xy).r)
    discard;*/
  FragColor = col;
}
