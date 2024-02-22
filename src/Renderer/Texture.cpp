#include <Texture.h>

void Texture::Load(const std::string texturePath) {
  glGenTextures(1, &_TextureID);
  glBindTexture(GL_TEXTURE_2D, _TextureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  _imageData = stbi_load(texturePath.c_str(), &_width, &_height, &_numColorChannels, 0);
  if (_imageData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, _imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "TEXTURE::LOAD::FAILURE" << std::endl;
  }
  stbi_image_free(_imageData);
}

void Texture::Bind(uint textureSlot) {
  glActiveTexture(GL_TEXTURE0 + textureSlot);
  glBindTexture(GL_TEXTURE_2D, _TextureID);
}
