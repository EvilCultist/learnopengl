#pragma once
#include <GL/glew.h>
#include <vector>

// #define use_rdr

class Renderer {
  private:
    GLfloat* vertices;
    GLuint* elements;
    GLuint numVertices;

  public:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint shaderProgram;
    Renderer(GLfloat* verts);
    void debug();
    int addPoint(GLfloat arr[8]);
    void setPoints();
    int addRenderElement(GLuint arr[3]);
    void setElements();
    int bindShaders(GLint vertex, GLint fragment);
    void render(GLuint indicies, GLsizei count);
    ~Renderer();
};

// GLuint ebo;
// glGenBuffers(1, &ebo);
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
//              GL_STATIC_DRAW);

// GLuint elements[] = {
//     0, 1, 2, 1, 2, 3, // top plane
//     4, 5, 6, 5, 6, 7, // bottom plane
//     0, 1, 4, 1, 4, 5, // left bl-wh
//     0, 2, 4, 2, 4, 6, // fwd
//     1, 3, 5, 3, 5, 7, // bck
//     2, 3, 6, 3, 6, 7, // right rd-green
// };

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

// GLfloat verts[] = {
//     -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no
//     13.5f,  -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // yeah no
//     13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // yeah no
//     13.5f,  13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // yeah no
//     -13.5f, 13.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // yeah no
//     -13.5f, -13.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no

//     -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
//     0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     0.5f,   0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     -0.5f,  0.5f,   -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no

//     -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
//     0.5f,   -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     -0.5f,  0.5f,   0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no

//     -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no
//     -0.5f,  0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     -0.5f,  -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     -0.5f,  -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // yeah no
//     -0.5f,  0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no

//     0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no
//     0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     0.5f,   -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // yeah no
//     0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // yeah no
//     0.5f,   0.5f,   0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // yeah no

//     -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no
//     0.5f,   -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     0.5f,   -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     -0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // yeah no
//     -0.5f,  -0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no

//     -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // yeah no
//     0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // yeah no
//     0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // yeah no
//     -0.5f,  0.5f,   0.5f,  1.0f, 0.5f, 0.5f, 0.0f, 0.0f, // yeah no
//     -0.5f,  0.5f,   -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //, 0.0f // yeah no
// };
