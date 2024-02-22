#include <Common.h>
#include <Engine.h>
#include <Shader.h>
#include <cmath>
#include <iostream>
#include <stb_image.h>
#include <sys/types.h>

int main() {

  std::cout << "The first step is to start." << std::endl;
  Engine::Run();
  /**
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(600, 800, "Weave", NULL, NULL);
  if (window == NULL) {
    std::cout << "window alloc failed" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  */
  Shader defaultShader;
  defaultShader.Load("../res/shaders/diag.vert.glsl",
                     "../res/shaders/color.frag.glsl");

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

  /* Texture Loading */
  u_int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, numColorChannels;
  u_char *imageData = stbi_load("../res/textures/brown_tiles.jpg", &width,
                                &height, &numColorChannels, 0);
  if (imageData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "TEXTURE::LOAD::FAILURE" << std::endl;
  }
  stbi_image_free(imageData);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);
  // glfwSetKeyCallback(window, toggle_wireframe_callback);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  /*
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.5f, 0.53f, 0.79f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    defaultShader.Use();

    float timeVal = glfwGetTime();
    float moveTri = (cos(timeVal) * 0.150f) / 0.32f;
    float changeCol = moveTri * 5;
    defaultShader.SetFloat("horizontalOffset", moveTri);
    defaultShader.SetFloat("strobeLight", changeCol);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  */
  return 0;
}
