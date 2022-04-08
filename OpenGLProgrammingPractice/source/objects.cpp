#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../header/noysoft/objects.h"

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
  glBindVertexArray(this->id[index]);
}

void VertexArrayObject::attribpointer(GLuint layout, GLuint ncomponents, GLenum type, GLsizeiptr stride, void* offset){
  glVertexAttribPointer(layout, ncomponents, type, GL_FALSE, stride, offset);
}

void VertexArrayObject::attribarray(int index){
  glEnableVertexAttribArray(index);
}


void VertexArrayObject::unbind(){
  glBindVertexArray(0);
}

unsigned int VertexArrayObject::getId(int index){
  return this->id[index];
}

void VertexArrayObject::clean(int size){
  glDeleteVertexArrays(size, this->id);
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

void VertexBufferObject::buffer(float vertices[], int size){
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBufferObject::unbind(){
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::clean(int size){
  glDeleteBuffers(size, this->id);
}

VertexBufferObject::~VertexBufferObject(){}

/////////////////////////////
/// ELement Buffer Object ///
/////////////////////////////

ElementBufferObject::ElementBufferObject(int size){
  this->id = new unsigned int[size];
}

void ElementBufferObject::generate(int size){
  glGenBuffers(size, this->id);
}

void ElementBufferObject::bind(int index){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id[index]);
}

void ElementBufferObject::buffer(int indices[], int size){
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBufferObject::unbind(){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::clean(int size){
  glDeleteBuffers(size, this->id);
}

ElementBufferObject::~ElementBufferObject(){}
