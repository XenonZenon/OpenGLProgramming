#ifndef CAMERA_H
#define CAMERA_H

#include "shaderutility.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include <string>

class Camera{

private:
  glm::mat4 view;
  glm::mat4 projection;

  glm::vec3 camerapos;
  glm::vec3 camerafront;
  glm::vec3 cameraup;

  int viewlocation;
  int projectionlocation;

public:
  Camera(glm::vec3, glm::vec3, glm::vec3);
  ~Camera();

  void setCameraFront(glm::vec3);
  void setView();
  void setProjection(float, float, float, float);
  void setUniformLocation(Shader, std::string, std::string);
  void setUniformMatrix();

  glm::vec3 getCameraPosition();

  void move(bool[], float);
};

#endif
