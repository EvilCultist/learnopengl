#include "renderer.h"
#include <iostream>

Renderer::Renderer(GLfloat* verts, size_t n_verts) {

    this->vertices = verts;
    // this->numVertices = 336; // 42 * 8
    this->numVertices = n_verts; // 42 * 8
    std::cout << n_verts << std::endl;

    // std::cout << vertices << std::endl;

    // for (int i = 0; i < 8 * 42; i += 8) {
    //     if (i % (8 * 6) == 0) {
    //         std::cout << std::endl;
    //     }
    //     for (int j = 0; j < 8; j++) {
    //         std::cout << *(this->vertices + i + j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->setPoints();

    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
void Renderer::debug() {
    // for (auto val : vertices) {
    //     std::cout << val << std::endl;
    // }
}
// int Renderer::addPoint(GLfloat arr[8]) {
//     // for (int i = 0; i < 8; i++) {
//     //     // std::cout << arr[i] << " ";
//     //     vertices.push_back(arr[i]);
//     // }
//     // std::cout << std::endl;
//     return 0; //
// }
void Renderer::setPoints() {
    glBufferData(GL_ARRAY_BUFFER, this->numVertices, this->vertices,
                 GL_STATIC_DRAW);
}
// int Renderer::addRenderElement(GLuint arr[3]) {
//     // for (int i = 0; i < 3; i++)
//     //     elements.push_back(arr[i]);
//     return 0; //
// }
// void Renderer::setElements() {
//     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), &elements[0],
//     //              GL_STATIC_DRAW);
// }
int Renderer::bindShaders(GLint vertex, GLint fragment) {

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertex);
    glAttachShader(this->shaderProgram, fragment);

    glBindFragDataLocation(this->shaderProgram, 0, "outColor");
    glLinkProgram(this->shaderProgram);
    glUseProgram(this->shaderProgram);

    GLint posAttrib = glGetAttribLocation(this->shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          0);

    GLint colAttrib = glGetAttribLocation(this->shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));

    GLint texAttrib = glGetAttribLocation(this->shaderProgram, "texCord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    return 0;
}
void Renderer::render(GLuint indicies, GLsizei count) {
    glDrawArrays(GL_TRIANGLES, indicies, count);

    // glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT,
    //                &elements[0] + indicies);
    return; //
}
Renderer::~Renderer() {
    glDeleteProgram(this->shaderProgram);
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
    return; //
}
