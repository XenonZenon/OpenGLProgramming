#ifndef UTILITY_H
#define UTILITY_H
#include <string>

class Shader{

private:
  unsigned int vertex = 0;
  unsigned int fragment = 0;
  unsigned int program = 0;

public:
  Shader(std::string, std::string);
  const char * readShader(std::string);
  unsigned int compileShader(std::string, std::string);
  void useProgram();
  unsigned int getVertex(){ return vertex; }
  unsigned int getFragment(){ return fragment; }
  unsigned int getProgram(){ return program; }
  void deleteProgram(unsigned int);
  ~Shader();
};

#endif
