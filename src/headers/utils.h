#pragma once
#include <GL/glew.h>
#include <chrono>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <string>

namespace utils {
class Timer {
  public:
    Timer();
    float now();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
void glfwHints();
std::string readFile(const std::string& filepath);
void getImage(std::string filePath, GLenum tex, GLint loc);
GLint makeShader(std::string path, GLenum type);
// void removeImage(unsigned char *image);
// void mkImage(const std::string &filepath);
}; // namespace utils
