#ifndef MODEL_H
#define MODEL_H

#include "shaderutility.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Model{

private:
  glm::mat4 model;

  int modellocation;

public:
  Model();
  ~Model();

  void setModel();
  void setScale(glm::vec3);
  void setRotate(float, glm::vec3);
  void setTranslate(glm::vec3);
  void setUniform(Shader, std::string);

  glm::mat4 getModel();

};

#endif
