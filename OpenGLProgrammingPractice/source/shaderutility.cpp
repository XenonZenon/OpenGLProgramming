#include "../header/shaderutility.h"
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(std::string vertex_filename, std::string fragment_filename){
  this->vertex = this->compileShader("vertex", vertex_filename);
  this->fragment = this->compileShader("fragment", fragment_filename);
  this->program = glCreateProgram();
  glAttachShader(this->program, this->vertex);
  glAttachShader(this->program, this->fragment);
  glLinkProgram(this->program);
}

const char * Shader::readShader(std::string filename){

  const char * code;
  std::string temp;
  std::string line;

  std::ifstream file(filename);
  if(file.is_open()){
    while(getline(file, line)){
      temp += line + "\n";
    }
  }
  code = temp.c_str();
  return code;
}

unsigned int Shader::compileShader(std::string type, std::string filename){

  if (type == "vertex") {
    const char * vertex = this->readShader(filename);
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex, NULL);
    glCompileShader(vertex_shader);
    return vertex_shader;
  }
  if(type == "fragment"){
    const char * fragment = this->readShader(filename);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment, NULL);
    glCompileShader(fragment_shader);
    return fragment_shader;
  }
  return 0;
}

void Shader::useProgram(unsigned int sProgram){
  glUseProgram(sProgram);
}

void Shader::deleteProgram(unsigned int sProgram){
  glDeleteProgram(sProgram);
}

void Shader::deleteShader(){
  glDeleteShader(this->vertex);
  glDeleteShader(this->fragment);
}

Shader::~Shader(){}
