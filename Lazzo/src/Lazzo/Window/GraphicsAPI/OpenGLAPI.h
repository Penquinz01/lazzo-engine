#pragma once
#include "GraphicsAPI.h"

class OpenGLAPI : public GraphicsAPI
{
public:
  OpenGLAPI(SDL_Window * window);
  ~OpenGLAPI();
  virtual void Init() override;
  virtual void SwapBuffers() override;
  virtual void Shutdown() override;

  SDL_GLContext glContext{};
};