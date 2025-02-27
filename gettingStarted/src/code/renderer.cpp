#include "renderer.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>

Renderer::Renderer(GLfloat* verts, size_t n_verts) {

    this->vertices = verts;
    this->numVertices = n_verts; // 42 * 8

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->setPoints();

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    this->elements = new GLuint[n_verts / (sizeof(GLfloat) * 8)];
    this->addRenderElements(n_verts / (sizeof(GLfloat) * 8));
    this->setElements();
}
void Renderer::debug() {
    // this->numVertices = 336; // 42 * 8
    // std::cout << n_verts << std::endl;

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
    // for (auto val : vertices) {
    //     std::cout << val << std::endl;
    // }
    // for (int i = 0; i < this->numVertices / (sizeof(GLfloat) * 8); i++)
    //     std::cout << *(this->elements + i) << std::endl;
}
void Renderer::setPoints() {
    glBufferData(GL_ARRAY_BUFFER, this->numVertices, this->vertices,
                 GL_STATIC_DRAW);
}
int Renderer::addRenderElements(size_t len) {
    for (int i = 0; i < len; i++)
        this->elements[i] = i;
    return 0; //
}
void Renderer::setElements() {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(GLuint) * (this->numVertices / (sizeof(GLfloat) * 8)),
                 this->elements, GL_STATIC_DRAW);
}
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
    // glDrawArrays(GL_TRIANGLES, indicies, count);
    // std::cout << count << '\t' << indicies << std::endl;

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT,
                   (void*)(indicies * sizeof(GLuint)));
    // this->elements + indicies);
    return; //
}
Renderer::~Renderer() {
    glDeleteProgram(this->shaderProgram);
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
    // this->debug();
    // free(this->elements);
    delete this->elements;
    return; //
}
