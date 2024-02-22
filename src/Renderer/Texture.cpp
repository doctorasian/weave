#include <Texture.h>

void Texture::Load(const std::string texturePath) {
  glGenTextures(1, &mTextureID);
  glBindTexture(GL_TEXTURE_2D, mTextureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  mImageData = stbi_load(texturePath.c_str(), &mWidth, &mHeight, &mNumColorChannels, 0);
  if (mImageData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, mImageData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "TEXTURE::LOAD::FAILURE" << std::endl;
  }
  stbi_image_free(mImageData);
}

void Texture::Bind(uint textureSlot) {
  glActiveTexture(GL_TEXTURE0 + textureSlot);
  glBindTexture(GL_TEXTURE_2D, mTextureID);
}
