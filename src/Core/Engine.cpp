#include <Core/GL.h>
#include <Engine.h>
#include <Renderer.h>

void Engine::Run() {
  GL::Init(1920, 1080);
  Init();
  /* Render Loop */
  while (GL::WindowIsOpen()) {
    GL::ProcessExitInput();
    Renderer::RenderFrame();
    GL::SwapBuffersPollEvents();
  }
  GL::Cleanup();
}

void Engine::Init() {
  /* load shaders and what not */
  Renderer::Init();
}
