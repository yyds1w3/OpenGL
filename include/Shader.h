#pragma once
#include <func.h>
class Shader
{
public:
    unsigned int m_ShaderProgram;
    Shader(const char *filepath, unsigned int &ShaderProgram);
};
