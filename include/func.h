#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

void Q_GLFWInit();
GLFWwindow* Q_MakeContextCurrent(unsigned int width, unsigned int height, const char *WindowName = "Hello");
void Q_GladInit();
unsigned int Q_CreatShaderProgram(const std::string &vertex, const std::string &fragment);
struct Q_ShaderSources{
    std::string VertexSource;
    std::string FragmentSource;
};

Q_ShaderSources Q_PraseShaderFile(const char *filepath);
