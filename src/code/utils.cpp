#include "utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/*#include <SOIL/SOIL.h>*/
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/geometric.hpp>

// glm::vec3 loc;
// glm::vec3 dir;
// glm::vec3 up;
utils::Timer::Timer() {
    auto start = std::chrono::high_resolution_clock::now();
}
// has some issue, returns a constant
float utils::Timer::now() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<float>>(end - start)
        .count();
}

void utils::glfwHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    /*glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);*/
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
}

// const char* readFile(const std::string& filePath) {
std::string utils::readFile(const std::string& filePath) {

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file at " << filePath << std::endl;
        return "";
    }

    std::string temp = "";
    std::string buffer = "";
    while (getline(file, temp))
        buffer += temp + '\n';
    // while (getline(vertex_s, temp))
    //     vertexSource += temp + '\n';
    file.close();
    // std::cout << buffer << std::endl;

    return buffer;
}

void utils::getImage(std::string filePath, GLenum tex, GLint loc) {
    glActiveTexture(tex);
    glBindTexture(GL_TEXTURE_2D, loc);
    int width, height, nrchannels;
    unsigned char* image =
        stbi_load(filePath.c_str(), &width, &height, &nrchannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    // settings functions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GLfloat textureBackground[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, textureBackground);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // import texture before this
    glGenerateMipmap(GL_TEXTURE_2D);
    /*SOIL_free_image_data(image);*/
}

int checkIfShaderDidOk(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        std::cerr << "vertex shader failed to compile" << std::endl;
        return -1;
    }
    return 0;
}

GLint utils::makeShader(std::string path, GLenum type) {
    std::string sourceString = utils::readFile(path);
    const char* source = sourceString.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    if (checkIfShaderDidOk(shader) == 0) {
        return shader;
    }
    return -1;
}

// void utils::removeImage(unsigned char *image) {}

// void utils::mkImage(const std::string &filepath) {
//   // wait for it
//   auto image = getImage(filepath);
//   GLuint tex;
//   glGenTextures(1, &tex);
//   glBindTexture(GL_TEXTURE_2D, tex);
//   // settings functions
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//   GLfloat textureBackground[] = {1.0f, 0.5f, 1.0f, 0.0f};
//   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
//   textureBackground); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//   GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//   GL_LINEAR); GLfloat pixels[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//                       0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
//   // import texture before this
//   glGenerateMipmap(GL_TEXTURE_2D);
//   removeImage(image);
// }
