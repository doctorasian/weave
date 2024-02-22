#include <GL.h>

namespace GL {
inline GLFWwindow *_window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processExitInput(GLFWwindow *window);

void GL::Init(int width, int height) {
  glfwInit();
  /* TODO update glfw package */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(600, 800, "Weave", NULL, NULL);
  if (_window == NULL) {
    std::cout << "GLFW Window Creation Failure" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void GL::ProcessExitInput() { processExitInput(_window); }

void GL::Cleanup() { glfwTerminate(); }

bool GL::WindowIsOpen() { return !glfwWindowShouldClose(_window); }

void GL::SwapBuffersPollEvents() {
  glfwSwapBuffers(_window);
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
