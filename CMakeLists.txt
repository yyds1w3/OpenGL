cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(glfwprojext)
 
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB project_file src/glad.c src/Application.cpp)
add_executable(Program ${project_file})
target_link_libraries(Program glfw OpenGL::GL)