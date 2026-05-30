#pragma once
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

namespace Lazzo
{
	class SDLWindow {
	public:
		SDLWindow(const char* title, int width, int height);
		~SDLWindow();
		void OnUpdate();

	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
	};
}