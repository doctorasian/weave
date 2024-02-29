#include <GL.h>

namespace GL {
inline GLFWwindow *window;
inline int window_width;
inline int window_height;
} // namespace GL

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processExitInput(GLFWwindow *window);

void GL::Init(int width, int height) {
  glfwInit();
  /* TODO update glfw package */
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
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

int GL::getWidth() { return window_width; }

int GL::getHeight() { return window_height; }

void GL::ProcessExitInput() { processExitInput(window); }

void GL::Cleanup() { glfwTerminate(); }

bool GL::WindowIsOpen() { return !glfwWindowShouldClose(window); }

void GL::SwapBuffersPollEvents() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processExitInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
