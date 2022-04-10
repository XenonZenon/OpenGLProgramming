#include "headercollection.h"

Model::Model(){
  this->model = glm::mat4(1.0f);
}

void Model::setModel(){
  this->model = glm::mat4(1.0f);
}

void Model::setScale(glm::vec3 scalesize){
  this->model = glm::scale(this->model, scalesize);
}

void Model::setRotate(float angle, glm::vec3 axis){
  this->model = glm::rotate(this->model, glm::radians(angle), axis);
}

void Model::setTranslate(glm::vec3 positions){
  this->model = glm::translate(this->model, positions);
}

void Model::setUniform(Shader shader, std::string model){
  this->modellocation = glGetUniformLocation(shader.getProgram(), model.c_str());
  glUniformMatrix4fv(this->modellocation, 1, GL_FALSE, glm::value_ptr(this->model));
}

glm::mat4 Model::getModel(){
  return this->model;
}

Model::~Model(){}
