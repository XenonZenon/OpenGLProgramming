#include "../header/noysoft/shaderutility.h"
#include "../header/noysoft/objects.h"
#include "../header/noysoft/texture.h"

#include "../header/glm/glm.hpp"
#include "../header/glm/gtc/matrix_transform.hpp"
#include "../header/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int width = 1200;
const unsigned int height = 620;

int main(){

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

  if(window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;

  glewInit();

  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Render: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  Shader shader("assets/shaders/vertex_shader.glsl", "assets/shaders/fragment_shader.glsl");

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  VertexArrayObject vao(1);
  VertexBufferObject vbo(1);
  ElementBufferObject ebo(1);

  vao.generate(1);
  vbo.generate(1);
  ebo.generate(1);

  vao.bind(0);
  vbo.bind(0);
  vbo.buffer(vertices, sizeof(vertices));
  ebo.bind(0);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.attribpointer(2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  vao.attribarray(2);
  vao.unbind();

/// Texture
  Texture texture(2);

  texture.generate(2);

  texture.bind(0);
  texture.parameters();
  texture.setTexture("assets/images/wall.jpg");
  texture.clean();
  texture.unbind();

  texture.bind(1);
  texture.parameters();
  texture.setTexture("assets/images/awesomeface.png");
  texture.clean();
  texture.unbind();

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection;

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

  int modellocation = glGetUniformLocation(shader.getProgram(), "model");
  int viewlocation= glGetUniformLocation(shader.getProgram(), "view");
  int projlocation = glGetUniformLocation(shader.getProgram(), "projection");

  int transformlocation = glGetUniformLocation(shader.getProgram(), "transform");

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.useProgram();

    /// Texture
    glActiveTexture(GL_TEXTURE0);
    texture.bind(0);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "unitexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    texture.bind(1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "unitexture2"), 1);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    /// Matrix
    glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewlocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projlocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformlocation, 1, GL_FALSE, glm::value_ptr(transform));

    vao.bind(0);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.unbind();

    glfwSwapBuffers(window);
  }
/// Clean Up
  shader.deleteProgram(shader.getProgram());
  vao.clean(1);
  vbo.clean(1);
  ebo.clean(1);
///
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if(key == GLFW_KEY_A && action == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if(key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  if(key == GLFW_KEY_V && action == GLFW_PRESS)
  {

  }
  if(key == GLFW_KEY_C && action == GLFW_PRESS)
  {

  }
}
