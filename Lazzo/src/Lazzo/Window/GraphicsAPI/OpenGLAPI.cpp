#pragma once
#include "lzpch.h"

#include "OpenGLAPI.h"

OpenGLAPI::OpenGLAPI(SDL_Window *window)
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  glContext = SDL_GL_CreateContext(window);
  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
}

OpenGLAPI::~OpenGLAPI()
{
  SDL_GL_DestroyContext(glContext);
}

void OpenGLAPI::Init()
{
}

void OpenGLAPI::SwapBuffers()
{
}

void OpenGLAPI::Shutdown()
{
}
