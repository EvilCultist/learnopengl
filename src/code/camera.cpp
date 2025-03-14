#include "camera.h"
/*#include <GLFW/glfw3.h>*/

Camera::Camera(glm::vec3 location, glm::vec3 up_direction) {
    this->loc = location;
    this->dir = -1.0f * glm::normalize(location);
    this->up = glm::normalize(up_direction);
}
void Camera::translate(glm::vec3 how_much) { //
    this->loc += how_much;
}
void Camera::rotate(glm::vec3 axis, float deg) { //
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(deg), axis);
    // dir = glm::normalize(rotation * glm::vec4(dir, 1.0f));
    this->dir = glm::normalize(rotation * glm::vec4(this->dir, 1.0f));
    // up = glm::normalize(rotation * glm::vec4(up, 1.0f));
};

glm::mat4 Camera::getView() { return glm::lookAt(this->loc, this->loc + this->dir, this->up); }

void Camera::updateScroll(GLFWwindow* window, double delx, double dely) {
    this->fov += dely;
    if (this->fov > 80)
        this->fov = 80;
    if (this->fov < 1)
        this->fov = 1;
}

int Camera::pollInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return -1;
    }
    const float speed = 0.06;
    glm::vec3 moveDir = glm::vec3(0.0f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        moveDir += this->up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        moveDir -= this->up;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        moveDir -= this->up;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_UP)) {
        // this->translate(this->dir * speed);
        moveDir += this->dir;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_DOWN)) {
        // this->translate(this->dir * speed * -1.0f);
        moveDir += -this->dir;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT)) {
        // this->translate(cross(this->dir, this->up) * speed);
        moveDir += glm::cross(this->dir, this->up);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_LEFT)) {
        // this->translate(cross(this->dir, this->up) * speed * -1.0f);
        moveDir += -glm::cross(this->dir, this->up);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        moveDir += this->up;
    }
    if (glm::length(moveDir) != 0) {
        this->translate(glm::normalize(moveDir) * speed);
    }
    return 0;
}
