#include <Common.h>
#include <Engine.h>
#include <Shader.h>
#include <cstdlib>
#include <iostream>
#include <stb_image.h>
#include <sys/types.h>

int main() {

  /* TODO: Upgrade Package 3.3 -> 4.x, Textures.h, Textures.c */
  std::cout << "The first step is to start." << std::endl;
  Engine::Run();
  return EXIT_SUCCESS;
  /* We've already sent our input vertex data to GPU and told it how to
   * interpret the data based on our vertex and fragment shaders. We still need
   * to... */
  /* Tell OpenGL how to interpret vertex data */
  /* TODO: Texture.cpp Texture Loading */
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

  return 0;
}
