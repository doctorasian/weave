#include <Common.h>

namespace GL {
void Init(int width, int height);
int getWidth();
int getHeight();
void ProcessExitInput();
void Cleanup();
bool WindowIsOpen();
void SwapBuffersPollEvents();
} // namespace GL
