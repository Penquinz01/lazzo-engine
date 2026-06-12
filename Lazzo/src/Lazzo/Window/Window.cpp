#include "lzpch.h"

#include "Window.h"
#include "Lazzo/Log.h"
#include <glad/glad.h>
#include "Events/Events.h"
#include "GraphicsAPI/GraphicsAPI.h"
#include "GraphicsAPI/OpenGLAPI.h"
#include "UI/ImguiUI.h"

namespace Lazzo {
	Window::Window(const char* title, int width, int height) {
    const char* glsl_version = "#version 460 core";
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			LZ_ERROR("SDL Couldnt be initialized Error:%s",SDL_GetError());
		}
		if(m_GraphicBackend == GraphicAPI::OpenGL) {
			m_Window = std::unique_ptr<SDL_Window, DeleteWindow>(
				SDL_CreateWindow(title,
					width,
					height,
					SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)
			);
			if (m_Window == nullptr) {
				LZ_ERROR("Error: SDL_CreateWindow(): %s", SDL_GetError());
				return;
			}
      m_GraphicsAPI = std::make_unique<OpenGLAPI>(m_Window.get());
		}
		gl_context = static_cast<OpenGLAPI*>(m_GraphicsAPI.get())->glContext;
    m_ImguiUI = std::make_unique<ImguiUI>(m_Window.get(), &gl_context);
	}
	Window::~Window()
	{
		SDL_DestroyWindow(m_Window.get());
		SDL_Quit();
	}

	bool Window::OnUpdate() {
		while (true) {
			while (SDL_PollEvent(&event))
			{
        m_ImguiUI->ProcessEvent(event);
				if (event.type == SDL_EVENT_QUIT) {
					return false;
				}
				switch (event.type) {
				case SDL_EVENT_KEY_DOWN:
					KeyDownEvent keyDownEvent(event);
					if (keyDownEvent.ReturnScanCode() == SDL_SCANCODE_ESCAPE) {
						return false;
					}
					LZ_TRACE("Key Down Event: {}", keyDownEvent.ReturnScanCode());
					break;
				}
			}
      m_ImguiUI->Render();
			SDL_GL_SwapWindow(m_Window.get());
		}
	}
	GraphicAPI Window::ChooseGraphicBackend() {
    return GraphicAPI::OpenGL;
	}
}