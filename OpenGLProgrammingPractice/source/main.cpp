#include "headercollection.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

bool keys[1024];
bool firstmouse = true;

const unsigned int windowwidth = 1360;
const unsigned int windowheight = 720;

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

int main(){

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, "OpenGL", glfwGetPrimaryMonitor(), nullptr);
  glfwSetWindowPos(window, 0, 0);
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

  Camera camera(camerapos, camerafront, cameraup);
  Model model;
  MemoryObject box;
  MemoryObject lamp;
  Texture container;
  Texture containerspecular;
  Shader boxshader("assets/shaders/vertex/lighting.vertex", "assets/shaders/fragment/lighting_map.fragment");
  Shader lampshader("assets/shaders/vertex/lamp.vertex", "assets/shaders/fragment/lamp.fragment");
  Light light;
  
  box.create(vertices, indices, sizeof(vertices), sizeof(indices), 8);
  lamp.create(vertices, indices, sizeof(vertices), sizeof(indices), 8);
  container.create("assets/images/container2.png");
  containerspecular.create("assets/images/container2_specular.png");
  container.activateandbind(GL_TEXTURE0);
  containerspecular.activateandbind(GL_TEXTURE1);

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

    // Draw Box
    boxshader.useProgram();
    light.setUniform(boxshader);
    /// Camera
    model.setModel();
    model.setTranslate(glm::vec3( 0.0f, 0.0f, 0.0f));
    model.setRotate(glfwGetTime() * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    model.setUniform(boxshader, "model");
    box.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    box.unbind();

    camera.setUniform(boxshader, "viewposition" , "view", "projection");
    ///

    // Draw Lamp
    lampshader.useProgram();

    model.setModel();
    model.setTranslate(light.getPosition());
    model.setScale(glm::vec3(0.2f));
    model.setUniform(lampshader, "model");

    lamp.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    lamp.unbind();

    camera.setUniform(lampshader, "viewposition", "view", "projection");

    glfwSwapBuffers(window);
  }
  /// Clean Up
  lampshader.deleteProgram(lampshader.getProgram());
  boxshader.deleteProgram(boxshader.getProgram());
  box.clean();
  lamp.clean();

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
