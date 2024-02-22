#include <Renderer.h>

void Renderer::RenderFrame() {
  glClearColor(0.5f, 0.53f, 0.70f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
