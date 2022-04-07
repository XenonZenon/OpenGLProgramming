#include "../header/shaderutility.h"
#include "../header/objects.h"
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(){

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(1200, 600, "OpenGL", nullptr, nullptr);

  if(window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  printf("Render: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  float vertices_2[] = {
    0.3f, 0.3f, 0.0f,
    0.3f, -0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f,
    -0.3f, 0.3f, 0.0f
  };

  unsigned int indices_2[] = {
    0, 1, 3,
    1, 2, 3
  };

  float firstTriangle[] = {
      -0.9f, -0.8f, 0.0f,  // Left
      -0.5f, -0.1f, 0.0f,  // Right
      -0.1f, -0.8f, 0.0f,  // Top
  };
  float secondTriangle[] = {
       0.0f, -0.5f, 0.0f,  // Left
       0.9f, -0.5f, 0.0f,  // Right
       0.45f, 0.5f, 0.0f   // Top
  };

/// Set Up
  Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
  shader.deleteShader();

  int size = 2;

  VertexArrayObject vao(size);
  VertexBufferObject vbo(size);

  vao.generate(size);
  vbo.generate(size);

  vao.bind(0);
  vbo.bind(0);
  vao.buffer(firstTriangle, sizeof(firstTriangle));
  vao.attribpointer(3 * sizeof(float));
  vao.unbind();

  vao.bind(1);
  vbo.bind(1);
  vao.buffer(secondTriangle, sizeof(secondTriangle));
  vao.attribpointer(3 * sizeof(float));
  vao.unbind();
///

  while(!glfwWindowShouldClose(window))
  {
    ///
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/// Render
    shader.useProgram(shader.getProgram());

    vao.bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.bind(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.unbind();
///
    glfwPollEvents();
    glfwSetKeyCallback(window, key_callback);
    glfwSwapBuffers(window);
  }
/// Clean Up

  shader.deleteProgram(shader.getProgram());
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
}
