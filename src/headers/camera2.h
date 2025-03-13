#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

class Camera2{
  public:
    double fov;

    glm::vec3 loc;
    glm::vec3 dir;
    glm::vec3 up;

    Camera2(glm::vec3 location, glm::vec3 up_direction);

    void translate(glm::vec3 how_much);
    void rotate(glm::vec3 axis, float deg);
    glm::mat4 getView();

    void updateScroll(GLFWwindow* window, double delx, double dely); 

    int pollInput(GLFWwindow* window);
};
