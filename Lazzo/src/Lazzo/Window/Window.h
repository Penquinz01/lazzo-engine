#pragma once
#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "GraphicsAPI/GraphicsAPI.h"

namespace Lazzo
{
	

	class Window {
	public:
		SDL_Event event{};
		Window(const char* title, int width, int height);
		~Window();
		bool OnUpdate();
	private:
		struct DeleteWindow {
			void operator()(SDL_Window* window) {
				SDL_DestroyWindow(window);
			}
		};
    std::unique_ptr<SDL_Window, DeleteWindow> m_Window{ nullptr };
    SDL_GLContext gl_context{};
    GraphicAPI m_GraphicBackend{ GraphicAPI::OpenGL };

		GraphicAPI ChooseGraphicBackend();
		float mainScale;
		//ImGuiIO* io{nullptr};

		

#pragma region testIMGUI
		bool show_demo_window{ true };
		float clear_color[4] = {0.45f, 0.55f, 0.60f, 1.00f};
		int counter{ 0 };

#pragma endregion
	};

	
}