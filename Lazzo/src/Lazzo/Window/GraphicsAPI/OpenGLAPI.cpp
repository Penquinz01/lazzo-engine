#include "OpenGLAPI.h"
#pragma once

OpenGLAPI::OpenGLAPI(SDL_Window *window)
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

OpenGLAPI::~OpenGLAPI()
{
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
