#include <GL/glew.h>
#include <GL/glext.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
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

  auto vertexSubjectShader =
      utils::makeShader("src/shaders/lighting.vert", GL_VERTEX_SHADER);
  auto fragmentSubjectShader =
      utils::makeShader("src/shaders/lighting.frag", GL_FRAGMENT_SHADER);

  auto vertexLightShader =
      utils::makeShader("src/shaders/light.vert", GL_VERTEX_SHADER);
  auto fragmentLightShader =
      utils::makeShader("src/shaders/light.frag", GL_FRAGMENT_SHADER);

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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // glm::vec3 ambientColor(1.0f, 1.0f, 1.0f);
  // glm::vec3 baseColor(1.0f, 0.5f, 0.31f);
  //
  // // auto rdr = new Renderer();
  //
  //
  // // rdr->bindShaders(vertexShader, fragmentShader);
  //
  // // GLint uniBase = glGetUniformLocation(rdr->shaderProgram,
  // "baseColor");
  // // GLint uniLightPos = glGetUniformLocation(rdr->shaderProgram,
  // "lightPos");
  // // GLint uniModel = glGetUniformLocation(rdr->shaderProgram, "model");
  // // GLint uniRot = glGetUniformLocation(rdr->shaderProgram, "rotation");
  // // GLint uniView = glGetUniformLocation(rdr->shaderProgram, "view");
  // // GLint uniProj = glGetUniformLocation(rdr->shaderProgram, "proj");
  //
  // // glUniform3fv(glGetUniformLocation(rdr->shaderProgram,
  // "ambientLight"), 1,
  // //              glm::value_ptr(ambientColor));
  // // glUniform3fv(uniBase, 1, glm::value_ptr(baseColor));
  //
  // auto view = Camera(                //
  //     glm::vec3(15.2f, 15.2f, 2.0f), //
  //     glm::vec3(0.0f, 0.0f, 1.0f)    //
  // );
  //
  // /*glUniformMatrix4fv(uniView, 1, GL_FALSE,
  // glm::value_ptr(view.getView()));*/
  //
  // // auto light = new Renderer();
  //
  // // light->bindShaders(vertexLightShader, fragmentLightShader);
  //
  // // GLint uniLightModel = glGetUniformLocation(light->shaderProgram,
  // "model");
  // // GLint uniLightView = glGetUniformLocation(light->shaderProgram,
  // "view");
  // // GLint uniLightProj = glGetUniformLocation(light->shaderProgram,
  // "proj");
  // //
  // // glUniform3fv(glGetUniformLocation(light->shaderProgram,
  // "ambientLight"), 1,
  // //              glm::value_ptr(ambientColor));
  //
  // /*auto vw = view.getView();*/
  // /*glUniformMatrix4fv(uniLightView, 1, GL_FALSE, &vw[0][0]);*/
  //
  // float time = 0;
  // auto t_now = std::chrono::system_clock::now();
  //
  // glEnable(GL_DEPTH_TEST);
  // glm::vec3 spawn_locations[N_BOXES];
  // for (int i = 0; i < N_BOXES; i++) {
  //   spawn_locations[i] =
  //       glm::vec3(((rand() % 42) / 2.0f) - 10.5f,
  //                 ((rand() % 42) / 2.0f) - 10.5f, ((rand() % 8) / 2.0f)
  //                 - 2.0f);
  // }
  // float spawn_angles[N_BOXES];
  // for (int i = 0; i < N_BOXES; i++) {
  //   spawn_angles[i] = rand() % 180;
  // }
  //
  // double prevx = 0, prevy = 0;
  // glfwGetCursorPos(window, &prevx, &prevy);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  //
  // glm::mat4 proj;
  //
  // while (!glfwWindowShouldClose(window)) {
  //   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //   // glUniformMatrix4fv(uniView, 1, GL_FALSE,
  //   glm::value_ptr(view.getView()));
  //
  //   t_now = std::chrono::system_clock::now();
  //   float t_diff =
  //   std::chrono::duration_cast<std::chrono::duration<float>>(
  //                      t_now - t_start)
  //                      .count();
  //   t_start = t_now;
  //   t_diff *= 0.2;
  //   time += t_diff;
  //   time = time - floor(time);
  //
  //   if (time <= 0.001) {
  //     baseColor =
  //         glm::vec3(((rand() % 256) / 256.0f), ((rand() % 256) / 256.0f),
  //                   ((rand() % 256) / 256.0f));
  //   }
  //
  //   glm::mat4 model = glm::mat4(1.0f);
  //   // glBindVertexArray(light->vao);
  //   // glUseProgram(light->shaderProgram);
  //
  //   // glUniformMatrix4fv(uniLightModel, 1, GL_FALSE,
  //   glm::value_ptr(model));
  //   // glUniformMatrix4fv(uniLightView, 1, GL_FALSE,
  //   //                    glm::value_ptr(view.getView()));
  //   proj = glm::perspective(glm::radians(view.fov),                //
  //                           (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
  //                           1.0f,                                  //
  //                           200.0f);
  //   // glUniformMatrix4fv(uniLightProj, 1, GL_FALSE, &proj[0][0]);
  //   //
  //   // light->render();
  //
  //   // glBindVertexArray(rdr->vao);
  //   // glUseProgram(rdr->shaderProgram);
  //   //
  //   // glUniform3fv(uniBase, 1, glm::value_ptr(baseColor));
  //   // // glUniform3fv(uniLightPos, 1, glm::value_ptr(baseColor));
  //   // glUniform3f(uniLightPos, model[0][3], model[1][3], model[2][3]);
  //   // glUniformMatrix4fv(uniView, 1, GL_FALSE,
  //   glm::value_ptr(view.getView()));
  //   //
  //   float temp = time;
  //   time = 1;
  //   for (int i = 0; i < N_BOXES; i++) {
  //     model = glm::mat4(1.0f);
  //     model = glm::translate(model, spawn_locations[i]);
  //     // model = glm::translate(model, glm::vec3(2.0f));
  //     glm::mat4 rot = glm::mat4(1.0);
  //     rot = glm::rotate(rot,                         // model,
  //                       glm::radians(360.0f) * time, // *
  //                       glm::radians(0.1f),
  //                       // glm::vec3(0.0f, 0.0f, 1.0f));
  //     rot = glm::rotate(rot, glm::radians(spawn_angles[i]),
  //     spawn_locations[i]);
  //     // glUniformMatrix4fv(uniModel, 1, GL_FALSE,
  //     glm::value_ptr(model));
  //     // glUniformMatrix4fv(uniRot, 1, GL_FALSE, glm::value_ptr(rot));
  //     // std::cout << time << std::endl;
  //
  //     // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  //     // rdr->render();
  //   }
  //   time = temp;
  //
  //   glDisable(GL_STENCIL_TEST);
  //
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  //
  //   double x, y;
  //   glfwGetCursorPos(window, &x, &y);
  //   x = prevx - x;
  //   y = prevy - y;
  //   prevx -= x;
  //   prevy -= y;
  //   // x = (((int)(x)) % 36000);
  //   // y = (((int)(y)) % 36000);
  //   auto mouse_move = glm::vec2(x, y);
  //   auto right_axis = glm::cross(
  //       view.dir,
  //       view.up - view.dir * glm::length(glm::dot(view.dir, view.up)));
  //
  //   if (glm::length(mouse_move) != 0) {
  //     mouse_move = glm::normalize(mouse_move);
  //     view.rotate(view.up, mouse_move.x * t_diff * 2000);
  //     view.rotate(right_axis, mouse_move.y * t_diff * 2000);
  //   }
  //
  //   if (view.pollInput(window) == -1)
  //     continue;
  //
  //   proj = glm::perspective(glm::radians(view.fov),                //
  //                           (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
  //                           1.0f,                                  //
  //                           200.0f);
  //   // glUniformMatrix4fv(uniProj, 1, GL_FALSE, &proj[0][0]);
  // }
  // // std::cout << view.dir.x << view.dir.y << view.dir.z << std::endl;
  // // std::cout << view.up.x << view.up.y << view.up.z << std::endl;
  // // std::cout << view.loc.x << view.loc.y << view.loc.z << std::endl;
  //
  // // glDeleteTextures(3, tex);
  //
  // // glDeleteProgram(rdr->shaderProgram);
  // // glDeleteBuffers(1, &rdr->vbo);
  // // glDeleteVertexArrays(1, &rdr->vao);
  // // delete rdr;
  // // delete light;
  //
  // glDeleteProgram(fragmentShader);
  // glDeleteProgram(vertexShader);
  //
  // // glDeleteBuffers(1, &ebo);
  // // glDeleteRenderbuffers(1, &rboDepthStencil);
  // // utils::removeImage(image);
  //
  // // std::this_thread::sleep_for(std::chrono::seconds(10));
  //
  // glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
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
