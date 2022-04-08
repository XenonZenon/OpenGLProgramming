#define STB_IMAGE_IMPLEMENTATION
#include "../header/stb/stbimage.h"
#include "../header/noysoft/texture.h"
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(int size){
  this->id = new unsigned int[size];
}

void Texture::generate(int size){
  glGenTextures(size, this->id);
}

void Texture::bind(int index){
  glBindTexture(GL_TEXTURE_2D, this->id[index]);
}

void Texture::parameters(){
  // set texture parameter
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::setTexture(std::string filepath){
  this->image = stbi_load(filepath.c_str(), &this->width, &this->height, &this->channels, 0);
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
}

unsigned char * Texture::getTexture(int index){
  return this->image;
}

void Texture::unbind(){
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clean(){
  stbi_image_free(this->image);
}

Texture::~Texture(){}
