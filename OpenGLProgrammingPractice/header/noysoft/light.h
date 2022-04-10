#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderutility.h"

class Light{

private:
  glm::vec3 lightpos;

public:
  Light();
  ~Light();

  void setUniform(Shader);
  glm::vec3 getPosition();

};

#endif
