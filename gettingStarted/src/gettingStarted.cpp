#include <GL/glew.h>
#include <chrono>
#include <cstdlib>
#include <cwchar>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
// #include <ios>
// #include <iostream>
#define GLFW_DLL
#include "camera.h"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
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

GLfloat verts[] = {
    -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no
    13.5f,  -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // yeah no
    13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // yeah no
    13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // yeah no
    -13.5f, 13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // yeah no
    -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no

    -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
    0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // yeah no
    0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
    0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
    -0.5f,  0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
    -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no

    -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
    0.5f,   -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // yeah no
    0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
    0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
    -0.5f,  0.5f,   0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // yeah no
    -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no

    -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no
    -0.5f,  0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
    -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
    -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
    -0.5f,  -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // yeah no
    -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no

    0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no
    0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
    0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
    0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
    0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
    0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no

    -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no
    0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
    0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
    0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
    -0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no
    -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no

    -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no
    0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
    0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
    0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
    -0.5f,  0.5f,   0.5f,  1.0f, 0.5f, 0.5f, 0.0f, 0.0f, // yeah no
    -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //, 0.0f // yeah no
};

int main() {
    auto t_start = std::chrono::system_clock::now();
    if (!glfwInit())
        return -1;

    utils::glfwHints();

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL",
                                          nullptr, nullptr);

    if (!window)
        return -1;

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        return -1;

#if defined use_rdr
    auto rdr = new Renderer(verts, sizeof(verts));
#endif

    auto vertexShader =
        utils::makeShader("src/shaders/triangle.vert", GL_VERTEX_SHADER);
    auto fragmentShader =
        utils::makeShader("src/shaders/triangle.frag", GL_FRAGMENT_SHADER);

#if defined(use_rdr)
    rdr->bindShaders(vertexShader, fragmentShader);
#endif

    GLuint tex[3];
    glGenTextures(3, tex);
    // glBindTexture(GL_TEXTURE_2D, tex);
    utils::getImage("res/mask.png", GL_TEXTURE1, tex[1]);
    utils::getImage("res/glass.png", GL_TEXTURE2, tex[2]);

#if defined(use_rdr)
    glUniform1i(glGetUniformLocation(rdr->shaderProgram, "texMask"), 1);
    glUniform1i(glGetUniformLocation(rdr->shaderProgram, "texGlass"), 2);
    GLint uniModel = glGetUniformLocation(rdr->shaderProgram, "model");
    GLint uniView = glGetUniformLocation(rdr->shaderProgram, "view");
    GLint uniProj = glGetUniformLocation(rdr->shaderProgram, "projection");
    auto uniOverride =
        glGetUniformLocation(rdr->shaderProgram, "overrideColor");
#endif

    auto view = Camera(                //
        glm::vec3(15.2f, 15.2f, 2.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f)    //
    );

    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view.getView()));

    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     std::cout << proj[i][j] << " ";
    //   }
    //   std::cout << std::endl;
    // }

    float time = 0;
    auto t_now = std::chrono::system_clock::now();
    // std::srand(
    //     (int)(10e7 *
    //           (float)std::chrono::duration_cast<std::chrono::duration<float>>(
    //               t_now - t_start)
    //               .count()));

    glEnable(GL_DEPTH_TEST);
    // std::cout << rand() % 10 << std::endl;
    // gen_boxes
    glm::vec3 spawn_locations[N_BOXES];
    for (int i = 0; i < N_BOXES; i++) {
        spawn_locations[i] = glm::vec3(
            (rand() % 22) / 2.0f, (rand() % 22) / 2.0f, (rand() % 8) / 2.0f);
        // std::cout << loc[i].x << ' ' << loc[i].y << ' ' << loc[i].z <<
        // std::endl;
    }
    float spawn_angles[N_BOXES];
    for (int i = 0; i < N_BOXES; i++) {
        spawn_angles[i] = rand() % 180;
    }

    double prevx = 0, prevy = 0;
    glfwGetCursorPos(window, &prevx, &prevy);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(uniView, 1, GL_FALSE,
                           glm::value_ptr(view.getView()));

        t_now = std::chrono::system_clock::now();
        float t_diff = std::chrono::duration_cast<std::chrono::duration<float>>(
                           t_now - t_start)
                           .count();
        t_start = t_now;
        t_diff *= 0.2;
        time += t_diff;
        time = time - floor(time);

        glUniform3f(uniOverride, 1.0f, 1.0f, 1.0f);

#if defined(use_rdr)
        glUseProgram(rdr->shaderProgram);
        glBindVertexArray(rdr->vao);
#endif

        for (int i = 0; i < N_BOXES; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, spawn_locations[i]);
            // model = glm::translate(model, glm::vec3(2.0f));
            model = glm::rotate(model, // model,
                                glm::radians(360.0f) *
                                    time, // * glm::radians(0.1f), //
                                glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::rotate(model, glm::radians(spawn_angles[i]),
                                spawn_locations[i]);
            glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
            // std::cout << time << std::endl;

            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
#if defined(use_rdr)
            rdr->render(6, 36);
#endif
        }

        glUniform3f(uniOverride, 0.4f, 0.4f, 0.4f);

        glEnable(GL_STENCIL_TEST);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);
        glDepthMask(GL_FALSE);
        glClear(GL_STENCIL_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        model =
            glm::rotate(model,                       // model,
                        glm::radians(360.0f) * time, // * glm::radians(0.1f),
                        glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

#if defined(use_rdr)
        rdr->render(0, 6);
#endif

        glDepthMask(GL_TRUE);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00);

        for (int i = 0; i < N_BOXES; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(spawn_locations[i].x,
                                                    spawn_locations[i].y,
                                                    -spawn_locations[i].z));
            // model = glm::translate(model, glm::vec3(2.0f));
            model = glm::rotate(model, // model,
                                glm::radians(360.0f) *
                                    time, // * glm::radians(0.1f), //
                                glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(                                      //
                glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)), // no
                glm::vec3(1.0f, 1.0f, -1.0f));
            model = glm::rotate(model, glm::radians(spawn_angles[i]),
                                spawn_locations[i]);
            glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
            // std::cout << time << std::endl;

#if defined(use_rdr)
            glUseProgram(rdr->shaderProgram);
            glBindVertexArray(rdr->vao);
            rdr->render(6, 36);
#endif

            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        glDisable(GL_STENCIL_TEST);

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
        // std::cout << right_axis.x << right_axis.y << right_axis.z <<
        // std::endl; std::cout << x << y << std::endl; std::cout << "time diff
        // - " << t_diff * 1000 << std::endl; std::cout << "mm - " <<
        // mouse_move.x << ' ' << mouse_move.y
        //           << std::endl;
        // if (glm::dot(view.up, view.dir) > 0.02) {
        //     std::cerr << "up and forward are not perpendicular" << std::endl;
        //     std::cerr << glm::dot(view.up, view.dir) << std::endl;
        // }

        if (view.pollInput(window) == -1)
            continue;

        glm::mat4 proj =
            glm::perspective(glm::radians(view.fov),                //
                             (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                             1.0f,                                  //
                             200.0f);
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    }
    // std::cout << view.dir.x << view.dir.y << view.dir.z << std::endl;
    // std::cout << view.up.x << view.up.y << view.up.z << std::endl;
    // std::cout << view.loc.x << view.loc.y << view.loc.z << std::endl;

    glDeleteTextures(3, tex);

#if defined(use_rdr)
    // glDeleteProgram(rdr->shaderProgram);
    // glDeleteBuffers(1, &rdr->vbo);
    // glDeleteVertexArrays(1, &rdr->vao);
    delete rdr;

#endif
    glDeleteProgram(fragmentShader);
    glDeleteProgram(vertexShader);

    // glDeleteBuffers(1, &ebo);
    // glDeleteRenderbuffers(1, &rboDepthStencil);
    // utils::removeImage(image);

    // std::this_thread::sleep_for(std::chrono::seconds(10));

    glfwTerminate();
    return 0;
}
