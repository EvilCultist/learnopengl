#include "renderer.h"
#include "utils.h"
#include <GL/gl.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

#define n_elems 12 * 3

Renderer::Renderer() {

    //                           n * n_pts
    this->vertices = (GLfloat*)calloc(8 * 3, sizeof(GLfloat));
    int s = 0;
    for (GLfloat i = -0.5f; i <= 0.5f; i++) {
        for (GLfloat j = -0.5f; j <= 0.5f; j++) {
            for (GLfloat k = -0.5f; k <= 0.5f; k++) {
                this->vertices[s * 3] = i;
                this->vertices[s * 3 + 1] = j;
                this->vertices[s * 3 + 2] = k;
                // std::cout << i << '\t' << j << '\t' << k << std::endl;
                s++;
            }
        }
    }

    this->numVertices = 8;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->setPoints();

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    this->addRenderElements(n_elems);
    this->setElements();
}
void Renderer::debug() {
    // for (int i = 0; i < n_elems; i++)
    //     std::cout << this->elements[i] << std::endl;
}
void Renderer::addRenderElements(size_t len) {
    GLuint elems[] = {0, 1, 2, 3, 7, 1, 5, 0, 4, 2, 6, 7, 4, 5};
    this->elements = new GLuint[len];
    for (int i = 0; i < 12; i++) {
        this->elements[(3 * i)] = elems[i];
        this->elements[(3 * i) + 1] = elems[i + 1];
        this->elements[(3 * i) + 2] = elems[i + 2];
    }
}
void Renderer::setPoints() {
    glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(GLfloat) * 3,
                 this->vertices, GL_STATIC_DRAW);
}
void Renderer::setElements() {
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //              sizeof(GLuint) * (this->numVertices / (sizeof(GLfloat) *
    //              8)), this->elements, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_elems * sizeof(GLuint),
                 this->elements, GL_STATIC_DRAW);
}
int Renderer::makeShader(std::string name) {
    auto vertexShader =
        utils::makeShader("src/shaders/" + name + ".vert", GL_VERTEX_SHADER);
    auto fragmentShader =
        utils::makeShader("src/shaders/" + name + ".frag", GL_FRAGMENT_SHADER);
    auto shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    this->shaderProgram.push_back(shader);
    return this->shaderProgram.size() - 1;
}
int Renderer::bindShaders(int choice) {

    glBindFragDataLocation(this->shaderProgram[choice], 0, "fragColor");
    glLinkProgram(this->shaderProgram[choice]);
    glUseProgram(this->shaderProgram[choice]);

    GLint posAttrib = glGetAttribLocation(this->shaderProgram[choice], "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          0);

    return 0;
}
void Renderer::render() {
    // glDrawArrays(GL_TRIANGLES, indicies, count);
    // std::cout << count << '\t' << indicies << std::endl;

    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT,
    //                (void*)(6 * sizeof(GLuint)));

    // glDrawElements(GL_TRIANGLE_STRIP, n_elems * sizeof(GLuint),
    // GL_UNSIGNED_INT,
    //                0);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, n_elems);

    glDrawElements(GL_TRIANGLES, n_elems * 3, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawArrays(GL_TRIANGLES, 3, 6);
    // this->elements + indicies);
}
Renderer::~Renderer() {
    for (auto val : this->shaderProgram)
        glDeleteProgram(val);
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
    this->debug();
    delete this->elements;
    free(this->vertices);
    return; //
}
