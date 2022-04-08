#include "../header/noysoft/shaderutility.h"
#include "../header/noysoft/objects.h"
#include "../header/noysoft/texture.h"
#include <iostream>
#include <string>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(){

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(1200, 620, "OpenGL", nullptr, nullptr);

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
    -0.2f, 0.3f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.2f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.8f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.8f, 0.3f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };



  float vertices_2[] = {
    0.8f, 0.3f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    0.8f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    0.2f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    0.2f, 0.3f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };

  float square[] = {
    // Positions          // Colors           // Texture Coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
  };

  int indices[] = {
    0, 1, 3,
    3, 1, 2
  };

/// Set Up
  Shader shader("assets/shaders/vertex_shader.glsl", "assets/shaders/fragment_shader.glsl");
  shader.deleteShader();

  int size = 3;

  VertexArrayObject vao(size);
  VertexBufferObject vbo(size);
  ElementBufferObject ebo(size);

  vao.generate(size);
  vbo.generate(size);
  ebo.generate(size);

  vao.bind(0);
  vbo.bind(0);
  vbo.buffer(vertices, sizeof(vertices));
  ebo.bind(0);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.attribarray(1);
  vao.attribpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  vao.attribarray(2);
  vao.unbind();

  vao.bind(1);
  vbo.bind(1);
  vbo.buffer(vertices_2, sizeof(vertices_2));
  ebo.bind(1);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.attribarray(1);
  vao.attribpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  vao.attribarray(2);
  vao.unbind();

//with texture
  vao.bind(2);
  vbo.bind(2);
  vbo.buffer(square, sizeof(square));
  ebo.bind(2);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.attribarray(1);
  vao.attribpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  vao.attribarray(2);
  vao.unbind();

/// Texture
  Texture texture(3);

  texture.generate(3);

  texture.bind(0);
  texture.parameters();
  texture.setTexture("assets/images/wall.jpg");
  texture.clean();
  texture.unbind();

  texture.bind(1);
  texture.parameters();
  texture.setTexture("assets/images/wood.jpg");
  texture.clean();
  texture.unbind();

  texture.bind(2);
  texture.parameters();
  texture.setTexture("assets/images/ice.jpg");
  texture.clean();
  texture.unbind();

  int nrAtrributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtrributes);
  std::cout << "Maximum nr of vertex attributes supported." << nrAtrributes << std::endl;

  while(!glfwWindowShouldClose(window))
  {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/// Shader Program
    shader.useProgram();
/// Render
    texture.bind(0);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "unitexture"), 0);
    vao.bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.unbind();

    texture.bind(1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "unitexture"), 0);
    vao.bind(1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.unbind();

    texture.bind(2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "unitexture"), 0);
    vao.bind(2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.unbind();
///
    glfwPollEvents();
    glfwSetKeyCallback(window, key_callback);
    glfwSwapBuffers(window);
  }
/// Clean Up
  shader.deleteProgram(shader.getProgram());
  vao.clean(size);
  vbo.clean(size);
  ebo.clean(size);
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
    glViewport(350, 50, 500, 500);
  }
  if(key == GLFW_KEY_C && action == GLFW_PRESS)
  {
    glViewport(0, 0, 1200, 620);
  }
}
