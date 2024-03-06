#include <GL.h>
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
         /* Position */        /* Color */     /* Texture */ 
      -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // front bot left       0
       0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // front bot right      1
       0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // front top right      2
      -0.5f,  0.5f,  0.0f,  0.5f, 0.3f, 0.2f,   0.0f, 1.0f, // front top left       3
	
      -0.5f, -0.5f,  -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // back bot left       4
       0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // back bot right      5
       0.5f,  0.5f,  -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // back top right      6
      -0.5f,  0.5f,  -0.5f,  0.5f, 0.3f, 0.2f,   0.0f, 1.0f, // back top left       7

  };
  unsigned int indices[]{
  	  0, 1, 2,
	  0, 3, 2, // front side

	  4, 5, 6,
	  4, 7, 6, // back side

	  0, 4, 1,
	  1, 5, 4, // bottom side
	  
	  3, 2, 7,
	  2, 6, 7, // top side

	  0, 4, 3,
	  4, 7, 3, // left side
	
	  1, 2, 6,
	  5, 1, 6 // right side
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
  glm::mat4 model = glm::mat4(1.0f);

  glm::mat4 view = GL::getCamera().GetViewMatrix();

  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(GL::getCamera().getZoom()),
                                (float)GL::getWidth() / (float)GL::getHeight(),
                                0.1f, 100.0f);

  uint modelLoc = glGetUniformLocation(shaders.geometry.ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  uint viewLoc = glGetUniformLocation(shaders.geometry.ID, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  uint projectionLoc = glGetUniformLocation(shaders.geometry.ID, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
