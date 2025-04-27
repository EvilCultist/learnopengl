#pragma once
#include <glm/vec3.hpp>

struct material {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
};

class Materials {
public:
  material *mats;
  Materials();
  ~Materials();
};
