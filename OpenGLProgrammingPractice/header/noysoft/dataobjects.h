#ifndef OBJECTS_H
#define OBJECTS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArrayObject{

private:
  unsigned int * id;

public:
  VertexArrayObject(int);
  ~VertexArrayObject();

  void generate(int);
  void bind(int);
  void attribarray(int);
  void attribpointer(GLuint, GLuint, GLenum, GLsizeiptr, void*);
  void unbind();
  unsigned int getId(int);

  void clean(int);

};

class VertexBufferObject{

private:
  unsigned int * id;

public:
  VertexBufferObject(int);
  ~VertexBufferObject();

  void generate(int);
  void bind(int);
  void buffer(float[], int);
  void unbind();

  void clean(int);

};

class ElementBufferObject{

private:
  unsigned int * id;

public:
  ElementBufferObject(int);
  ~ElementBufferObject();

  void generate(int);
  void bind(int);
  void buffer(int[], int);
  void unbind();

  void clean(int);

};

#endif
