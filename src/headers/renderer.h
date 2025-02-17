#pragma once
#include <GL/glew.h>
#include <vector>

class Renderer {
  private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> elements;

  public:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint shaderProgram;
    Renderer();
    int addPoint(GLfloat arr[8]);
    void setPoints();
    int addRenderElement(GLuint arr[3]);
    void setElements();
    int bindShaders(GLint vertex, GLint fragment);
    void render(GLuint indicies, GLsizei count);
    ~Renderer();
};

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
