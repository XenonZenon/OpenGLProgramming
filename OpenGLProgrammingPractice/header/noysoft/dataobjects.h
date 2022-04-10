#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MemoryObject{

private:
  GLuint vao;
  GLuint vbo;
  GLuint ebo;

public:
  MemoryObject();
  ~MemoryObject();

  void bind();
  void unbind();
  void create(float[], int[], unsigned int, unsigned int, int);
  void clean();
};

#endif
