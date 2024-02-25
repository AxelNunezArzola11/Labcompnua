# Project settings
cmake_minimum_required(VERSION 3.5)
project(practica0)


# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)


# Required libraries installed in the system

## OpenGL
set(OpenGL_GL_PREFERENCE GLVND) # Set OpenGL version
find_package(OpenGL REQUIRED)

## GLFW3
find_package(glfw3 3.3 REQUIRED)

## GLEW
find_package(GLEW REQUIRED)

## GLM
find_package(glm REQUIRED)
# Source files
add_executable(
  ${PROJECT_NAME} src/practica2.cpp
  src/Mesh.cpp
  src/Shader.cpp
  src/Window.cpp
  shaders/shader.vert
  shaders/shadercolor.vert
  shaders/azul_shader.vert
  shaders/cafe_shader.vert
  shaders/roja_shader.vert
  shaders/verde_shader.vert
shaders/verde_oscuro_shader.vert
  shaders/shader.frag
  shaders/shadercolor.frag
  
)
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
# Linked libraries settings
target_link_libraries(${PROJECT_NAME}
  OpenGL::GL
  GLEW
  glfw
  glm::glm
  Xrandr
  Xi
  Xinerama
  Xcursor
)
