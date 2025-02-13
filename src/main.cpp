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
#include <ios>
#include <iostream>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils.h>

// #define WINDOW_HEIGHT 1200
#define WINDOW_HEIGHT 800
// #define WINDOW_WIDTH 2200
#define WINDOW_WIDTH 1200
#define N_BOXES 8

void renderCube() { ; }

float fov = 45.0f;

void updateScroll(GLFWwindow* window, double delx, double dely) {
    fov += dely;
    if (fov > 80)
        fov = 80;
    if (fov < 1)
        fov = 1;
}

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

    // GLfloat vertices[] = {
    //     //  Position         Color             Texcoords
    //     0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 0 -
    //     Bottom-right -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 1
    //     - Bottom-left 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 2
    //     - Top-right -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 3 -
    //     Top-left 0.5f,  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 4 -
    //     Bottom-right -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 5
    //     - Bottom-left 0.5f,  0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 6
    //     - Top-right -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 7 -
    //     Top-left 0.5f,  0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // 6 -
    //     Top-right
    // };

    GLfloat vertices[] = {
        -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, // yeah no
        13.5f,  -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, // yeah no
        13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.10f, 1.0f, // yeah no
        13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, // yeah no
        -13.5f, 13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, // yeah no
        -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, // yeah no

        -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, // yeah no
        0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f, // yeah no
        0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, // yeah no
        0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, // yeah no
        -0.5f,  0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, // yeah no
        -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, // yeah no

        -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, // yeah no
        0.5f,   -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, // yeah no
        0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  1.0f, // yeah no
        0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  1.0f, // yeah no
        -0.5f,  0.5f,   0.5f,  1.0f, 0.0f, 1.0f, 0.0f,  1.0f, // yeah no
        -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, // yeah no

        -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, // yeah no
        -0.5f,  0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, // yeah no
        -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, // yeah no
        -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, // yeah no
        -0.5f,  -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, // yeah no
        -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, // yeah no

        0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, // yeah no
        0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, // yeah no
        0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, // yeah no
        0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, // yeah no
        0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, // yeah no
        0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, // yeah no

        -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f, // yeah no
        0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, // yeah no
        0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, // yeah no
        0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, // yeah no
        -0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  0.0f, // yeah no
        -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f, // yeah no

        -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f, // yeah no
        0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, // yeah no
        0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, // yeah no
        0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, // yeah no
        -0.5f,  0.5f,   0.5f,  1.0f, 0.5f, 0.5f, 0.0f,  0.0f, // yeah no
        -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f //, 0.0f // yeah no
    };

    // GLuint elements[] = {
    //     0, 1, 2, 1, 2, 3, // top plane
    //     4, 5, 6, 5, 6, 7, // bottom plane
    //     0, 1, 4, 1, 4, 5, // left bl-wh
    //     0, 2, 4, 2, 4, 6, // fwd
    //     1, 3, 5, 3, 5, 7, // bck
    //     2, 3, 6, 3, 6, 7, // right rd-green
    // };

    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLuint rboDepthStencil;
    glGenRenderbuffers(1, &rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH,
                          WINDOW_HEIGHT);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // GLuint ebo;
    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
    // GL_STATIC_DRAW);

    auto vertexShader =
        utils::makeShader("src/shaders/triangle.vert", GL_VERTEX_SHADER);
    auto fragmentShader =
        utils::makeShader("src/shaders/triangle.frag", GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texCord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));

    // GLuint tex;
    // glGenTextures(1, &tex);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, tex);

    GLuint tex[3];
    glGenTextures(3, tex);
    // glBindTexture(GL_TEXTURE_2D, tex);
    utils::getImage("res/mask.png", GL_TEXTURE1, tex[1]);
    utils::getImage("res/glass.png", GL_TEXTURE2, tex[2]);

    glUniform1i(glGetUniformLocation(shaderProgram, "texMask"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "texGlass"), 2);

    glm::mat4 model = glm::mat4(0.5f);
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    // glm::mat4 view = glm::lookAt(      //
    //     glm::vec3(15.2f, 15.2f, 2.0f), //
    //     glm::vec3(0.0f, 0.0f, 0.f),    //
    //     glm::vec3(0.0f, 0.0f, 1.0f)    //
    // );

    // auto original_location_vector = glm::vec3(15.2f, 15.2f, 2.0f);
    // auto default_up_vector = glm::vec3(0.0f, 0.0f, 1.0f);
    // auto view = Camera(           //
    //     original_location_vector, //
    //                               // glm::vec3(-1.5f, -1.5f, -0.2f), //
    //     glm::dot(original_location_vector, default_up_vector) -
    //         default_up_vector //
    // );
    auto view = Camera(                //
        glm::vec3(15.2f, 15.2f, 2.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f)    //
    );

    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view.getView()));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f),                   //
                                      (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                                      1.0f,                                  //
                                      200.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    auto uniOverride = glGetUniformLocation(shaderProgram, "overrideColor");

    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     std::cout << proj[i][j] << " ";
    //   }
    //   std::cout << std::endl;
    // }

    float time = 0;
    auto t_now = std::chrono::system_clock::now();
    std::srand(
        (int)(10e7 *
              (float)std::chrono::duration_cast<std::chrono::duration<float>>(
                  t_now - t_start)
                  .count()));

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
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

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
            glDrawArrays(GL_TRIANGLES, 6, 36);
        }

        glUniform3f(uniOverride, 0.4f, 0.4f, 0.4f);

        glEnable(GL_STENCIL_TEST);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);
        glDepthMask(GL_FALSE);
        glClear(GL_STENCIL_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        // model =
        //     glm::rotate(model,                       // model,
        //                 glm::radians(360.0f) * time, // * glm::radians(0.1f),
        //                 // glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 6);

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

            glUseProgram(shaderProgram);

            glBindVertexArray(vao);

            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 6, 36);
        }

        // glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        // glDrawArrays(GL_TRIANGLES, 6, 36);
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

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            continue;
        }
        const float speed = 0.03;
        glm::vec3 moveDir = glm::vec3(0.0f);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_UP)) {
            // view.translate(view.dir * speed);
            moveDir += view.dir;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_DOWN)) {
            // view.translate(view.dir * speed * -1.0f);
            moveDir += -view.dir;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_RIGHT)) {
            // view.translate(cross(view.dir, view.up) * speed);
            moveDir += glm::cross(view.dir, view.up);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_LEFT)) {
            // view.translate(cross(view.dir, view.up) * speed * -1.0f);
            moveDir += -glm::cross(view.dir, view.up);
        }
        if (glm::length(moveDir) != 0) {
            view.translate(glm::normalize(moveDir) * speed);
        }
        glfwSetScrollCallback(window, updateScroll);
        glm::mat4 proj =
            glm::perspective(glm::radians(fov),                     //
                             (1.0f * WINDOW_WIDTH) / WINDOW_HEIGHT, //
                             1.0f,                                  //
                             200.0f);
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    }
    // std::cout << view.dir.x << view.dir.y << view.dir.z << std::endl;
    // std::cout << view.up.x << view.up.y << view.up.z << std::endl;
    // std::cout << view.loc.x << view.loc.y << view.loc.z << std::endl;

    glDeleteTextures(3, tex);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(fragmentShader);
    glDeleteProgram(vertexShader);

    // glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteRenderbuffers(1, &rboDepthStencil);

    glDeleteVertexArrays(1, &vao);

    // utils::removeImage(image);

    // std::this_thread::sleep_for(std::chrono::seconds(10));

    glfwTerminate();
    return 0;
}
