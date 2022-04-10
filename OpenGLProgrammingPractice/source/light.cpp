#include "headercollection.h"


Light::Light(){
  this->lightpos = glm::vec3(1.2f, 1.0f, 2.0f);
}

void Light::setUniform(Shader shader){
  /// light position
  glUniform3f(glGetUniformLocation(shader.getProgram(), "light.position"), this->lightpos.x, this->lightpos.y, this->lightpos.z);
  // light properties
  glUniform3f(glGetUniformLocation(shader.getProgram(), "light.ambient"), 0.3f, 0.3f, 0.3f);
  glUniform3f(glGetUniformLocation(shader.getProgram(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
  glUniform3f(glGetUniformLocation(shader.getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);

  glUniform1i(glGetUniformLocation(shader.getProgram(), "material.diffuse"), 0);
  glUniform1i(glGetUniformLocation(shader.getProgram(), "material.specular"), 1);
  glUniform1f(glGetUniformLocation(shader.getProgram(), "material.shininess"), 128.0f);
}

glm::vec3 Light::getPosition(){
  return this->lightpos;
}

Light::~Light(){}
