#include "renderer.h"

Renderer::Renderer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
int Renderer::addPoint(GLfloat arr[8]) {
    for (int i = 0; i < 8; i++)
        vertices.push_back(arr[i]);
    return 0; //
}
void Renderer::setPoints() {
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0],
                 GL_STATIC_DRAW);
}
int Renderer::addRenderElement(GLuint arr[3]) {
    for (int i = 0; i < 3; i++)
        elements.push_back(arr[i]);
    return 0; //
}
void Renderer::setElements() {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), &elements[0],
                 GL_STATIC_DRAW);
}
int Renderer::bindShaders(GLint vertex, GLint fragment) {

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);

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
    return 0;
}
void Renderer::render(GLuint indicies, GLsizei count) {

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT,
                   &elements[0] + indicies);
    return; //
}
Renderer::~Renderer() {
    return; //
}
