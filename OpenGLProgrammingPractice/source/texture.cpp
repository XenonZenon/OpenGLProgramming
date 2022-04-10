#define STB_IMAGE_IMPLEMENTATION
#include <stb/stbimage.h>
#include "headercollection.h"

Texture::Texture(){
  glGenTextures(1, &this->id);
}

void Texture::create(std::string filepath){
  glBindTexture(GL_TEXTURE_2D, this->id);
  this->image = stbi_load(filepath.c_str(), &this->width, &this->height, &this->channels, STBI_rgb);
  if(this->image == NULL){
    std::cout << "//////////////////////////////////" << std::endl;
    std::cout << "/// MAY MALI: loading image... ///" << std::endl;
    std::cout << "//////////////////////////////////" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                this->width, this->height,
                0, GL_RGB, GL_UNSIGNED_BYTE,
                this->image);
  glGenerateMipmap(GL_TEXTURE_2D);
  // set texture parameter
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_image_free(this->image);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activateandbind(int enumlevel){
  glActiveTexture(enumlevel);
  glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture(){}
