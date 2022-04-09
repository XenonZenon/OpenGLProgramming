#include "../header/noysoft/shaderutility.h"
#include "../header/noysoft/dataobjects.h"
#include "../header/noysoft/texture.h"
#include "../header/noysoft/camera.h"
#include "../header/noysoft/model.h"

#include "../header/glm/glm.hpp"
#include "../header/glm/gtc/matrix_transform.hpp"
#include "../header/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

bool keys[1024];
bool firstmouse = true;

const unsigned int windowwidth = 1200;
const unsigned int windowheight = 620;

// Camera
glm::vec3 camerapos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);

float pitch = 0.0f;
float yaw = 0.0f;

float lastx = windowwidth/2;
float lasty = windowheight/2;

float fov = 45.0f;

// Frame
float deltatime = 0.0f;
float lastframe = 0.0f;

// Light
glm::vec3 lightpos = glm::vec3(1.2f, 1.0f, 2.0f);

int main(){

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, "OpenGL", nullptr, nullptr);
  glfwSetWindowPos(window, 100, 100);
  glfwShowWindow(window);

  if(window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();
  glViewport(0, 0, windowwidth, windowheight);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Render: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  float vertices[] = {
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };

  int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  /// Setting the Data Objects
  VertexArrayObject vao(2);
  VertexBufferObject vbo(2);
  ElementBufferObject ebo(2);

  vao.generate(2);
  vbo.generate(2);
  ebo.generate(2);

  vao.bind(0);
  vbo.bind(0);
  vbo.buffer(vertices, sizeof(vertices));
  ebo.bind(0);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.attribpointer(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
  vao.attribarray(1);
  vao.attribpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
  vao.attribarray(2);
  vao.unbind();

  /// Light VAO
  vao.bind(1);
  vbo.bind(1);
  vbo.buffer(vertices, sizeof(vertices));
  ebo.bind(1);
  ebo.buffer(indices, sizeof(indices));
  vao.attribpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vao.attribarray(0);
  vao.unbind();

  Shader lighting("assets/shaders/vertex/lighting.vertex", "assets/shaders/fragment/lighting_map.fragment");
  Shader lamp("assets/shaders/vertex/lamp.vertex", "assets/shaders/fragment/lamp.fragment");

  Camera camera(camerapos, camerafront, cameraup);
  Model model;

  Texture texture(2);
  texture.generate(2);

  texture.bind(0);
  texture.parameters();
  texture.setTexture("assets/images/container2.png");
  texture.clean();
  texture.unbind();

  texture.bind(1);
  texture.parameters();
  texture.setTexture("assets/images/container2_specular.png");
  texture.clean();
  texture.unbind();

  lighting.useProgram();
  glUniform1i(glGetUniformLocation(lighting.getProgram(), "material.diffuse"), 0);
  glUniform1i(glGetUniformLocation(lighting.getProgram(), "material.specular"), 1);

  while(!glfwWindowShouldClose(window))
  {
    float currentframe = glfwGetTime();
    deltatime = currentframe - lastframe;
    lastframe = currentframe;

    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera View
    camera.setCameraFront(camerafront);
    camera.move(keys, deltatime);
    camera.setProjection(fov, (float)windowwidth/(float)windowheight, 0.1f, 100.0f);
    camera.setView();

    lighting.useProgram();
    /// light
    int lightpositionlocation = glGetUniformLocation(lighting.getProgram(), "light.position");
    int viewpositionlocation = glGetUniformLocation(lighting.getProgram(), "viewposition");
    glUniform3f(lightpositionlocation, lightpos.x, lightpos.y, lightpos.z);
    glUniform3f(viewpositionlocation, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    // light properties
    glUniform3f(glGetUniformLocation(lighting.getProgram(), "light.ambient"), 0.3f, 0.3f, 0.3f);
    glUniform3f(glGetUniformLocation(lighting.getProgram(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(lighting.getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);

    glUniform1f(glGetUniformLocation(lighting.getProgram(), "material.shininess"), 128.0f);

    /// Camera
    camera.setUniformLocation(lighting, "view", "projection");
    camera.setUniformMatrix();

    glActiveTexture(GL_TEXTURE0);
    texture.bind(0);
    glActiveTexture(GL_TEXTURE1);
    texture.bind(1);

    // Draw
    model.setModel();
    model.setTranslate(glm::vec3( 0.0f, 0.0f, 0.0f));
    model.setRotate(glfwGetTime() * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    model.setUniformLocation(lighting, "model");
    model.setUniformMatrix();
    vao.bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.unbind();
    ///

    lamp.useProgram();

    camera.setUniformLocation(lamp, "view", "projection");
    camera.setUniformMatrix();

    // Draw
    model.setModel();
    model.setTranslate(lightpos);
    model.setScale(glm::vec3(0.2f));
    model.setUniformLocation(lamp, "model");
    model.setUniformMatrix();
    vao.bind(1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.unbind();

    glfwSwapBuffers(window);
  }
  /// Clean Up
  lamp.deleteProgram(lamp.getProgram());
  lighting.deleteProgram(lighting.getProgram());
  vao.clean(2);
  vbo.clean(2);
  ebo.clean(2);

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

  if(action == GLFW_PRESS)
  {
    keys[key] = true;
  }
  else if(action == GLFW_RELEASE)
  {
    keys[key] = false;
  }
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
  if(fov >= 1.0f && fov <= 45.0f)
  {
    fov -= yoffset;
  }
  if(fov <= 1.0f)
  {
    fov = 1.0f;
  }
  if(fov >= 45.0f)
  {
    fov = 45.0f;
  }
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
  if(firstmouse)
  {
    lastx = xpos;
    lasty = ypos;
    firstmouse = false;
  }

  float xoffset = xpos - lastx;
  float yoffset = lasty - ypos;
  lastx = xpos;
  lasty = ypos;

  float sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if(pitch > 89.0f)
  {
    pitch = 89.0f;
  }
  if(pitch < -89.0f)
  {
    pitch = -89.0f;
  }
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin (glm::radians(yaw));
  camerafront = glm::normalize(front);
}
