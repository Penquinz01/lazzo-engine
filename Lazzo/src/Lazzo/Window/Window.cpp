#include "Window.h"
#include "Lazzo/Log.h"
#include <glad.h>

namespace Lazzo {
	SDLWindow::SDLWindow(const char* title, int width, int height) {
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			LZ_ERROR("SDL Couldnt be initialized Error:%s",SDL_GetError());
		}
		if (!SDL_CreateWindowAndRenderer("Lazzo Engine",640,480,SDL_WINDOW_RESIZABLE,&m_Window,&m_Renderer)) {
			LZ_ERROR("SDL Couldn't Create a Window or Renderer Error Code:%s",SDL_GetError());
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	}
}