#include <GL/glew.h>
#include <GL/glext.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <shader.h>
// #include <ios>
// #include <iostream>

#include <GL/gl.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <camera_log.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <materials.h>
#include <renderer.h>
#include <utils.h>

// #define WINDOW_HEIGHT 1200
#define WINDOW_HEIGHT 800
// #define WINDOW_WIDTH 2200
#define WINDOW_WIDTH 1200
#define N_BOXES 8

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0, 0.0, 1.0));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightLoc(0.0, 0.0, 0.0);

int main() {
  auto t_start = std::chrono::system_clock::now();
  if (!glfwInit())
    return -1;

  utils::glfwHints();

  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);

  if (!window)
    return -1;

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    return -1;

  glEnable(GL_DEPTH_TEST);

  Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");
  Shader subjectShader("src/shaders/lighting.vert",
                       "src/shaders/lighting.frag");

  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // comm
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  // comm
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,   // comm
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,   // comm
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  // comm
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // comm
                                              //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // comm
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,    // comm
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,     // comm
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,     // comm
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,    // comm
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // comm
                                              //
      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   // comm
      -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  // comm
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // comm
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // comm
      -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,  // comm
      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   // comm
                                              //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,     // comm
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,    // comm
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,   // comm
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,   // comm
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    // comm
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,     // comm
                                              //
      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // comm
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  // comm
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,   // comm
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,   // comm
      -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,  // comm
      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // comm
                                              //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // comm
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,    // comm
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,     // comm
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,     // comm
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,    // comm
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // comm
  };

  GLuint subject_vao, subject_vbo, light_vao, light_vbo;

  glGenVertexArrays(1, &subject_vao);
  glGenVertexArrays(1, &light_vao);

  glGenBuffers(1, &subject_vbo);
  // glGenBuffers(1, &light_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, subject_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

  glBindVertexArray(subject_vao);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, subject_vbo);

  glBindVertexArray(light_vao);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, subject_vbo);

  glm::vec3 ambientColor(1.0f, 1.0f, 1.0f);
  glm::vec3 baseColor(1.0f, 0.5f, 0.31f);

  float time = 0;
  auto t_now = std::chrono::system_clock::now();

  glm::vec3 spawn_locations[N_BOXES];
  for (int i = 0; i < N_BOXES; i++) {
    spawn_locations[i] =
        glm::vec3(((rand() % 42) / 2.0f) - 10.5f,
                  ((rand() % 42) / 2.0f) - 10.5f, ((rand() % 8) / 2.0f) - 2.0f);
  }
  // spawn_locations[N_BOXES - 1] = glm::vec3(32.0f, 0.0f, 0.0f);

  float spawn_angles[N_BOXES];
  for (int i = 0; i < N_BOXES; i++) {
    spawn_angles[i] = rand() % 180;
  }

  auto materials = new Materials();

  double prevx = 0, prevy = 0;
  glfwGetCursorPos(window, &prevx, &prevy);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glm::mat4 proj;

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view.getView()));

    processInput(window);

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    t_now = std::chrono::system_clock::now();
    float t_diff = std::chrono::duration_cast<std::chrono::duration<float>>(
                       t_now - t_start)
                       .count();
    t_start = t_now;
    t_diff *= 0.2;
    time += t_diff;
    time = time - floor(time);

    if (time <= 0.001) {
      baseColor =
          glm::vec3(((rand() % 256) / 256.0f), ((rand() % 256) / 256.0f),
                    ((rand() % 256) / 256.0f));
    }

    lightShader.use();
    lightShader.setVec3("ambientLight", ambientColor);

    glm::mat4 model = glm::mat4(1.0f);
    auto proj = glm::perspective(glm::radians(camera.Zoom),             //
                                 (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                                 1.0f,                                  //
                                 200.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::vec3 lightLocation =
        (float)sin(time * 3.1415 * 2) * glm::vec3(0.0f, 0.0f, 8.0f);
    model = glm::translate(model, lightLocation);
    lightShader.setMat4("model", model);
    lightShader.setMat4("view", view);
    lightShader.setMat4("proj", proj);

    glBindVertexArray(light_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    subjectShader.use();
    subjectShader.setVec3("lightPos", lightLocation);
    subjectShader.setVec3("viewPos", camera.Position);
    subjectShader.setMat4("view", view);
    subjectShader.setMat4("proj", proj);

    for (int i = 0; i < N_BOXES; i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, spawn_locations[i]);
      subjectShader.setMat4("model", model);
      glm::mat4 rot = glm::mat4(1.0);
      // std::cout << time << std::endl;
      rot = glm::rotate(rot, glm::radians(spawn_angles[i] + 360 * time),
                        spawn_locations[i]);
      subjectShader.setMat4("rotation", rot);
      // std::cout << materials->mats[i].shininess << " ";
      int matIndex = i * 2;
      subjectShader.setVec3("material.ambient",
                            materials->mats[matIndex].ambient);
      subjectShader.setVec3("material.diffuse",
                            materials->mats[matIndex].diffuse);
      subjectShader.setVec3("material.specular",
                            materials->mats[matIndex].specular);
      subjectShader.setFloat("material.shininess",
                             materials->mats[matIndex].shininess);

      glBindVertexArray(subject_vao);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    // std::cout << std::endl;
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // std::cout << view.dir.x << view.dir.y << view.dir.z << std::endl;
  // std::cout << view.up.x << view.up.y << view.up.z << std::endl;
  // std::cout << view.loc.x << view.loc.y << view.loc.z << std::endl;

  // glDeleteTextures(3, tex);

  // glDeleteProgram(rdr->shaderProgram);
  // glDeleteBuffers(1, &rdr->vbo);
  // glDeleteVertexArrays(1, &rdr->vao);
  // delete rdr;
  // delete light;

  // glDeleteProgram(fragmentShader);
  // glDeleteProgram(vertexShader);

  // glDeleteBuffers(1, &ebo);
  // glDeleteRenderbuffers(1, &rboDepthStencil);
  // utils::removeImage(image);

  // std::this_thread::sleep_for(std::chrono::seconds(10));
  delete materials;

  glDeleteVertexArrays(1, &light_vao);
  glDeleteVertexArrays(1, &subject_vao);
  glDeleteBuffers(1, &subject_vbo);
  // glDeleteBuffers(1, &light_vbo);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(UP, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.ProcessKeyboard(DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    camera.ProcessKeyboard(DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {

  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
