#include <Camera.h>
#include <Core/GL.h>
#include <Engine.h>
#include <Renderer.h>

void Engine::Run() {
  GL::Init(1920, 1080);
  Engine::Init();
  Camera freeCamera(glm::vec3(0.0f, 0.0f, 3.0f));
  bool mouseOffset = false;
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  /* Render Loop */
  while (GL::WindowIsOpen()) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    GL::ProcessInput(deltaTime);
    Renderer::RenderFrame();
    GL::SwapBuffersPollEvents();
  }
  GL::Cleanup();
}

void Engine::Init() {
  /* load shaders and what not */
  Renderer::Init();
}
