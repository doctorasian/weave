#include "Camera.h"
#include "GLFW/glfw3.h"
#include <GL.h>

namespace GL {
bool mouseOffset = false;
inline GLFWwindow *window;
inline Camera camera;
inline int window_width;
inline int window_height;
} // namespace GL

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processExitInput(GLFWwindow *window);

void GL::Init(int width, int height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "Weave", NULL, NULL);
  window_width = width;
  window_height = height;
  if (window == NULL) {
    std::cout << "GLFW Window Creation Failure" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

int GL::getWidth() { return window_width; }

int GL::getHeight() { return window_height; }

Camera GL::getCamera() { return camera; }

void GL::ProcessInput(float deltaTime) {
  processExitInput(window);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

void GL::Cleanup() { glfwTerminate(); }

bool GL::WindowIsOpen() { return !glfwWindowShouldClose(window); }

void GL::SwapBuffersPollEvents() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  static float lastX = GL::getWidth() / 2.0f;
  static float lastY = GL::getHeight() / 2.0f;
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (!GL::mouseOffset) {
    lastX = xpos;
    lastY = ypos;
    GL::mouseOffset = true;
  }
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  GL::camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  GL::camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processExitInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
