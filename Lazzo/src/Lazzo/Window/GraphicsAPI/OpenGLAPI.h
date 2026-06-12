#pragma once
#include "GraphicsAPI.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"

class OpenGLAPI : public GraphicsAPI
{
public:
  OpenGLAPI(SDL_Window * window);
  ~OpenGLAPI();
  virtual void Init() override;
  virtual void SwapBuffers() override;
  virtual void Shutdown() override;
  inline virtual SDL_GLContext GetContext() const override { return glContext; }

  SDL_GLContext glContext{};
};