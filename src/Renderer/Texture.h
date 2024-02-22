#include <Common.h>
#include <stb_image.h>
#include <string>

class Texture {
public:
  void Load(const std::string texturePath);
  void Bind(uint textureSlot);
  uint GetID();
  int GetWidth();
  int GetHeight();
private:
  uint mTextureID = 0;
  u_char *mImageData = nullptr;
  int mNumColorChannels = 0;
  int mWidth = 0;
  int mHeight = 0;
};
