#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#define GLFW_DLL
#include <GLFW/glfw3.h>

class Camera {
  public:
    float fov = 45.0f;

    glm::vec3 loc;
    glm::vec3 dir;
    glm::vec3 up;

    Camera(glm::vec3 location, glm::vec3 up_direction);
    void translate(glm::vec3 how_much);
    void rotate(glm::vec3 axis, float deg);
    void updateScroll(GLFWwindow* window, double delx, double dely);
    int pollInput(GLFWwindow* window);
    glm::mat4 getView();
};
