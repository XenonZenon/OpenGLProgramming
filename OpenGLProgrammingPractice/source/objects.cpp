#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../header/objects.h"

///////////////////////////
/// Vertex Array Object ///
///////////////////////////

VertexArrayObject::VertexArrayObject(int size){
  this->id = new unsigned int[size];
}

void VertexArrayObject::generate(int size){
  glGenVertexArrays(size, this->id);
}

void VertexArrayObject::bind(int index){
  glEnableVertexAttribArray(1);
  glBindVertexArray(this->id[index]);
}

void VertexArrayObject::buffer(float vertices[], int size){
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexArrayObject::attribpointer(int size){
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, (void*)0);
}

void VertexArrayObject::unbind(){
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

unsigned int VertexArrayObject::getId(int index){
  return this->id[index];
}

VertexArrayObject::~VertexArrayObject(){}

////////////////////////////
/// Vertex Buffer Object ///
////////////////////////////

VertexBufferObject::VertexBufferObject(int size){
  this->id = new unsigned int[size];
}

void VertexBufferObject::generate(int size){
  glGenBuffers(size, this->id);
}

void VertexBufferObject::bind(int index){
  glBindBuffer(GL_ARRAY_BUFFER, this->id[index]);
}

void VertexBufferObject::unbind(){
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject(){}
