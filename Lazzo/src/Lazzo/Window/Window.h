#pragma once
#include "SDL3/SDL.h"

namespace Lazzo
{
	class SDLWindow {
	public:
		SDL_Event event{};
		SDLWindow(const char* title, int width, int height);
		~SDLWindow();
		bool OnUpdate();
	private:
		SDL_Window* m_Window{};
		SDL_Renderer* m_Renderer{};
	};
}