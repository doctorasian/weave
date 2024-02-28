#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Shaders {
  Shader geometry;
} shaders;

void createShape();
void drawShape();

void Renderer::Init() {
  shaders.geometry.Load("../res/shaders/diag.vert.glsl",
                        "../res/shaders/color.frag.glsl");
  createShape();
}

void Renderer::RenderFrame() {
  glClearColor(0.5f, 0.53f, 0.70f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  shaders.geometry.Use();
  drawShape();
}
/**
dumping stuff here temporarily
*/
void createShape() {
  uint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // clang-format off
  float vertices[] = {
      -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bot left
       0.5f, -0.5f,  0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bot right
       0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      -0.5f,  0.5f, -1.0f, 0.5f, 0.3f, 0.2f, 0.0f, 1.0f, // top left
  };
  unsigned int indices[]{
      0, 1, 2, 
      0, 3, 2,
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));

  uint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, numChannels;
  u_char *imageData = stbi_load("../res/textures/brown_tiles.jpg", &width,
                                &height, &numChannels, 0);
  if (imageData) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "LOAD TEXTURE FAILURE\n";
  }
  stbi_image_free(imageData);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
}

void drawShape() {
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans, glm::vec3(0.25f,0.25f,0.0f));
  trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
  trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
  uint transformLoc = glGetUniformLocation(shaders.geometry.ID, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}
