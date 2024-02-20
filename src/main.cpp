// clang-format off
#include <cmath>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <shader.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void toggle_wireframe_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    GLint i = 0;
    glGetIntegerv(GL_POLYGON_MODE, &i);
    glPolygonMode(GL_FRONT_AND_BACK, i == GL_FILL ? GL_FILL : GL_LINE);
  }
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main() {

  /*std::cout << "Life is but a sensory illusion. If our ultimate "
               "destiny is death, the stop of sensory influx, then why "
               "live to facilitate the processing of it? - Santanu"
            << std::endl;
  */
  glfwInit();
  /* set opengl req. for ver 3.3 */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(600, 800, "Weave", NULL, NULL);
  if (window == NULL) {
    std::cout << "window alloc failed" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Shader defaultShader("../assets/shaders/diag.vert.glsl",
                       "../assets/shaders/color.frag.glsl");

  /* We've already sent our input vertex data to GPU and told it how to
   * interpret the data based on our vertex and fragment shaders. We still need
   * to... */
  /* Tell OpenGL how to interpret vertex data */
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // clang-format off
  float vertices[] = {
      -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // bot left
      0.5f,  -0.5f, 0.3f, 0.0f, 1.0f, 0.0f,// bot right
      0.5f,  0.5f,  1.0f,  1.0f, 0.0f, 0.0f,// top right
      -0.5f, 0.5f,  -1.0f, 0.5f, 0.3f, 0.2f,// top left
      0.0f,  0.7f,  0.0f, 0.0f, 0.7f, 0.3f,// tip
  };
  unsigned int indices[]{
      0, 1, 2, 
      0, 3, 2,
      2, 3, 4
  };
  // clang-format on
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);
  // glfwSetKeyCallback(window, toggle_wireframe_callback);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  /* Render Loop */
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.5f, 0.53f, 0.79f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    defaultShader.use();

    float timeVal = glfwGetTime();
    float moveTri = (cos(timeVal) * 0.150f) / 0.32f;
    float changeCol = moveTri * 5;
    defaultShader.setFloat("horizontalOffset", moveTri);
    defaultShader.setFloat("strobeLight", changeCol);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
