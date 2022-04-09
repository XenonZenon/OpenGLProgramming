#include "../header/noysoft/shaderutility.h"
#include "../header/noysoft/camera.h"

#include "../header/glm/glm.hpp"
#include "../header/glm/gtc/matrix_transform.hpp"
#include "../header/glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 camerapos, glm::vec3 camerafront, glm::vec3 cameraup){
  this->view = glm::mat4(1.0f);
  this->camerapos = camerapos;
  this->camerafront = camerafront;
  this->cameraup = cameraup;
}

void Camera::setCameraFront(glm::vec3 camerafront){
  this->camerafront = camerafront;
}

void Camera::setView(){
  this->view = glm::lookAt(this->camerapos, this->camerapos + this->camerafront, this->cameraup);
}

void Camera::setProjection(float fov, float aspectratio, float nearplane, float farplane){
  this->projection = glm::perspective(glm::radians(fov), aspectratio, nearplane, farplane);
}

void Camera::setUniformLocation(Shader shader, std::string uniview, std::string uniprojection){
  this->viewlocation = glGetUniformLocation(shader.getProgram(), uniview.c_str());
  this->projectionlocation = glGetUniformLocation(shader.getProgram(), uniprojection.c_str());
}

void Camera::setUniformMatrix(){
  glUniformMatrix4fv(this->viewlocation, 1, GL_FALSE, glm::value_ptr(this->view));
  glUniformMatrix4fv(this->projectionlocation, 1, GL_FALSE, glm::value_ptr(this->projection));
}

glm::vec3 Camera::getCameraPosition(){
  return this->camerapos;
}

void Camera::move(bool keys[], float deltatime){

  float cameraspeed = 5.0f * deltatime;

  if(keys[GLFW_KEY_W])
  {
    this->camerapos += cameraspeed * this->camerafront;
  }
  if(keys[GLFW_KEY_S])
  {
    this->camerapos -= cameraspeed * this->camerafront;
  }
  if(keys[GLFW_KEY_A])
  {
    this->camerapos -= glm::normalize(glm::cross(this->camerafront, this->cameraup)) * cameraspeed;
  }
  if(keys[GLFW_KEY_D])
  {
    this->camerapos += glm::normalize(glm::cross(this->camerafront, this->cameraup)) * cameraspeed;
  }
}

Camera::~Camera(){}
