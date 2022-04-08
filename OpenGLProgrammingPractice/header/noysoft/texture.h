#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture{

private:
  unsigned int * id;
  unsigned char * image;
  int width;
  int height;
  int channels;

public:
  Texture(int);
  ~Texture();

  void generate(int);
  void bind(int);
  void parameters();
  void setTexture(std::string);
  unsigned char * getTexture(int);
  void unbind();
  void clean();

};

#endif
