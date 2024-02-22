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
  uint _TextureID = 0;
  u_char *_imageData = nullptr;
  int _numColorChannels = 0;
  int _width = 0;
  int _height = 0;
};
