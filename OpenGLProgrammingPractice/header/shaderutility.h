#ifndef UTILITY_H
#define UTILITY_H
#include <string>

class Shader{

private:
  unsigned int vertex = 0;
  unsigned int fragment = 0;
  unsigned int program = 0;

public:
  Shader();
  ~Shader();
  const char * readShader(std::string, std::string);
  unsigned int compileShader(std::string, std::string);
  void setVertexShader(std::string);
  void setFragmentShader(std::string);
  void setProgram();
  void useProgram(unsigned int);
  unsigned int getVertex(){ return vertex; }
  unsigned int getFragment(){return fragment; }
  unsigned int getProgram(){ return program; }
  void deleteShader();
};

#endif
