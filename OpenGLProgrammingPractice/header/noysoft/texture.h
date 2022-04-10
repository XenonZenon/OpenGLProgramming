#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture{

private:
  GLuint id;
  unsigned char * image;
  int width;
  int height;
  int channels;

public:
  Texture();
  ~Texture();

  void create(std::string);
  void activateandbind(int);

};

#endif
