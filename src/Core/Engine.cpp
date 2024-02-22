#include <Core/GL.h>
#include <Renderer.h>
#include <Engine.h>

void Engine::Run() {
  GL::Init(1920, 1080);

  /* Render Loop */
  while (GL::WindowIsOpen()) {
    GL::ProcessExitInput();
    Renderer::RenderFrame();
    GL::SwapBuffersPollEvents();
  }
}
