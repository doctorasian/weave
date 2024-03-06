#include "Camera.h"
#include <Common.h>

namespace GL {
void Init(int width, int height);
int getWidth();
int getHeight();
Camera getCamera();
void ProcessInput(float deltaTime);
void Cleanup();
bool WindowIsOpen();
void SwapBuffersPollEvents();
} // namespace GL
