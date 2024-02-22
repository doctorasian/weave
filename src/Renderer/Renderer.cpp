#include <Renderer.h>
#include <Shader.h>
#include <cmath>

struct Shaders {
  Shader geometry;
} shaders;

void drawTriangle();

void Renderer::Init() {
  shaders.geometry.Load("../res/shaders/diag.vert.glsl",
                         "../res/shaders/color.frag.glsl");
}

void Renderer::RenderFrame() {
  glClearColor(0.5f, 0.53f, 0.70f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  shaders.geometry.Use();
  drawTriangle();
}

void drawTriangle() {
  uint VAO;
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
  uint VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  uint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  float timeVal = glfwGetTime();
  float moveTri = cos(timeVal) * 0.750f;
  float changeCol = moveTri * 5;
  shaders.geometry.SetFloat("horizontalOffset", moveTri);
  shaders.geometry.SetFloat("strobeLight", changeCol);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
