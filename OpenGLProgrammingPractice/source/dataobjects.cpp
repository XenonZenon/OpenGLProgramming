#include "headercollection.h"

MemoryObject::MemoryObject(){
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
  glGenBuffers(1, &this->ebo);
}

void MemoryObject::bind(){
  glBindVertexArray(1);
}

void MemoryObject::unbind(){
  glBindVertexArray(0);
}

void MemoryObject::create(float vertices[], int indices[], unsigned int vertisize, unsigned int indisize, int stridesize){
  // VAO
  glBindVertexArray(1);
  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, vertisize, vertices, GL_STATIC_DRAW);
  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indisize, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stridesize * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stridesize * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stridesize * sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void MemoryObject::clean(){
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  glDeleteBuffers(1, &this->ebo);
}

MemoryObject::~MemoryObject(){}
