#pragma once

#include "sg.h"

uint32_t sgCompileShader (int stage, char const* source, int size);

uint32_t sgLinkShaderProgram (uint32_t* shaderv, int shaderc);
