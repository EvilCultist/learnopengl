#include <GL/glew.h>
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
#define GLFW_DLL
/*#define GLFW_*/
#include "camera.h"
#include <GLFW/glfw3.h>
/*#include <stb_image.h>*/
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <renderer.h>
#include <shader.h>
#include <utils.h>
/*#include <camera2.h>*/

/*#define WINDOW_HEIGHT 1200*/
#define WINDOW_HEIGHT 800
/*#define WINDOW_WIDTH 2200*/
#define WINDOW_WIDTH 1200

#define N_BOXES 14

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

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    return -1;

  glEnable(GL_DEPTH_TEST);

  auto object = new Renderer();
  auto light = new Renderer();

  Shader lightShadr("src/shaders/lighting.vert", "src/shaders/lighting.frag");

  int lightShader = light->makeShader("lightSource");
  light->bindShaders();

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 baseColor(1.0f, 0.5f, 0.31f);

  GLint uniLightModel = glGetUniformLocation(light->shaderProgram, "model");
  GLint uniLightView = glGetUniformLocation(light->shaderProgram, "view");
  GLint uniLightProj = glGetUniformLocation(light->shaderProgram, "proj");
  glUniform3f(glGetUniformLocation(light->shaderProgram, "lightColor"), 1.0f,
              1.0f, 1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glUniformMatrix4fv(uniLightModel, 1, GL_FALSE, glm::value_ptr(model));

  int cubeShader = object->makeShader("lighting");
  object->bindShaders();

  GLint uniBase = glGetUniformLocation(object->shaderProgram, "baseColor");
  GLint uniModel = glGetUniformLocation(object->shaderProgram, "model");
  GLint uniView = glGetUniformLocation(object->shaderProgram, "view");
  GLint uniProj = glGetUniformLocation(object->shaderProgram, "proj");

  glUniform3fv(glGetUniformLocation(object->shaderProgram, "lightColor"), 1,
               glm::value_ptr(lightColor));
  glUniform3fv(uniBase, 1, glm::value_ptr(baseColor));

  // glUniform3fv(uniBase, 1, glm::value_ptr(lightColor));

  auto view = Camera(              //
      glm::vec3(5.2f, 5.2f, 2.0f), //
      glm::vec3(0.0f, 0.0f, 1.0f)  //
  );

  float time = 0;
  auto t_now = std::chrono::system_clock::now();

  glEnable(GL_DEPTH_TEST);
  glm::vec3 spawn_locations[N_BOXES];
  for (int i = 0; i < N_BOXES; i++) {
    spawn_locations[i] =
        glm::vec3(((rand() % 42) / 2.0f) - 10.5f,
                  ((rand() % 42) / 2.0f) - 10.5f, ((rand() % 8) / 2.0f) - 2.0f);
  }
  float spawn_angles[N_BOXES];
  for (int i = 0; i < N_BOXES; i++) {
    spawn_angles[i] = rand() % 180;
  }

  double prevx = 0, prevy = 0;
  glfwGetCursorPos(window, &prevx, &prevy);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view.getView()));
    glUniformMatrix4fv(uniLightView, 1, GL_FALSE,
                       glm::value_ptr(view.getView()));

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
      /*std::cout << baseColor.x << " " << baseColor.y << " " << baseColor.z*/
      /*          << std::endl;*/
    }
    model = glm::mat4(1.0f);
    glUniformMatrix4fv(uniLightModel, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(light->vao);
    light->bindShaders();
    light->render();

    glBindVertexArray(object->vao);
    object->bindShaders();

    for (int i = 0; i < N_BOXES; i++) {
      glUniform3fv(uniBase, 1, glm::value_ptr(baseColor));
      model = glm::mat4(1.0f);
      model = glm::translate(model, spawn_locations[i]);
      // model = glm::translate(model, glm::vec3(2.0f));
      model =
          glm::rotate(model,                       // model,
                      glm::radians(360.0f) * time, // * glm::radians(0.1f), //
                      glm::vec3(0.0f, 0.0f, 1.0f));
      model =
          glm::rotate(model, glm::radians(spawn_angles[i]), spawn_locations[i]);
      glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
      // std::cout << time << std::endl;

      // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
      object->render();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    x = prevx - x;
    y = prevy - y;
    prevx -= x;
    prevy -= y;
    // x = (((int)(x)) % 36000);
    // y = (((int)(y)) % 36000);
    auto mouse_move = glm::vec2(x, y);
    auto right_axis = glm::cross(
        view.dir,
        view.up - view.dir * glm::length(glm::dot(view.dir, view.up)));

    if (glm::length(mouse_move) != 0) {
      mouse_move = glm::normalize(mouse_move);
      view.rotate(view.up, mouse_move.x * t_diff * 2000);
      view.rotate(right_axis, mouse_move.y * t_diff * 2000);
    }

    if (view.pollInput(window) == -1)
      continue;

    glm::mat4 proj = glm::perspective(glm::radians(view.fov),                //
                                      (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                                      1.0f,                                  //
                                      200.0f);
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(uniLightProj, 1, GL_FALSE,
                       glm::value_ptr(glm::perspective(
                           glm::radians(view.fov),                //
                           (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                           1.0f,                                  //
                           200.0f)));
  }
  // std::cout << view.dir.x << view.dir.y << view.dir.z << std::endl;
  // std::cout << view.up.x << view.up.y << view.up.z << std::endl;
  // std::cout << view.loc.x << view.loc.y << view.loc.z << std::endl;

  // glDeleteTextures(3, tex);

  // glDeleteBuffers(1, &object->vbo);
  // glDeleteVertexArrays(1, &object->vao);
  delete object;

  // glDeleteBuffers(1, &ebo);
  // utils::removeImage(image);

  // std::this_thread::sleep_for(std::chrono::seconds(10));

  glfwTerminate();
  return 0;
}
