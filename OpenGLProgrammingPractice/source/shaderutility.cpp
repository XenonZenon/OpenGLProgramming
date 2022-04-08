#include "../header/noysoft/shaderutility.h"
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(std::string vertexsource, std::string fragmentsource){
  this->vertex = this->compileShader("vertex", vertexsource);
  this->fragment = this->compileShader("fragment", fragmentsource);
  this->program = glCreateProgram();
  glAttachShader(this->program, this->vertex);
  glAttachShader(this->program, this->fragment);
  glLinkProgram(this->program);
  glDeleteShader(this->vertex);
  glDeleteShader(this->fragment);
}

const char * Shader::readShader(std::string filepath){

  const char * code;
  std::string temp;
  std::string line;

  std::ifstream file(filepath);
  if(file.is_open()){
    while(getline(file, line)){
      temp += line + "\n";
    }
  }
  code = temp.c_str();
  return code;
}

unsigned int Shader::compileShader(std::string type, std::string filepath){

  if (type == "vertex") {
    const char * vertex = this->readShader(filepath);
    unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vertex, NULL);
    glCompileShader(vertexshader);
    return vertexshader;
  }
  if(type == "fragment"){
    const char * fragment = this->readShader(filepath);
    unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &fragment, NULL);
    glCompileShader(fragmentshader);
    return fragmentshader;
  }
  return 0;
}

void Shader::useProgram(){
  glUseProgram(this->program);
}

void Shader::deleteProgram(unsigned int program){
  glDeleteProgram(program);
}

Shader::~Shader(){}
