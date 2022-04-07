#ifndef OBJECTS_H
#define OBJECTS_H

class VertexArrayObject{

private:
  unsigned int * id;

public:
  VertexArrayObject(int);
  ~VertexArrayObject();

  void generate(int);
  void bind(int);
  void buffer(float[], int);
  void attribpointer(int);
  void unbind();
  unsigned int getId(int);

};

class VertexBufferObject{

private:
  unsigned int * id;

public:
  VertexBufferObject(int);
  ~VertexBufferObject();

  void generate(int);
  void bind(int);
  void unbind();

};
#endif
