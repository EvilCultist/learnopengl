#pragma once
#include <chrono>
#include <string>
#define GLFW_DLL
#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

class Camera {
public:
  glm::vec3 loc;
  glm::vec3 dir;
  glm::vec3 up;

  Camera(glm::vec3 location, glm::vec3 direction, glm::vec3 up_direction);
  void translate(glm::vec3 how_much);
  void rotate(glm::vec3 axis, float deg);
  glm::mat4 getView();
};

namespace utils {
class Timer {
public:
  Timer();
  float now();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
void glfwHints();
std::string readFile(const std::string &filepath);
void getImage(std::string filePath, GLenum tex, GLint loc);
GLint makeShader(std::string path, GLenum type);
// void removeImage(unsigned char *image);
// void mkImage(const std::string &filepath);
} // namespace utils
