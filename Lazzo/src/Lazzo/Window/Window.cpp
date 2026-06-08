#include "lzpch.h"

#include "Window.h"
#include "Lazzo/Log.h"
#include <glad/glad.h>
#include "Events/Events.h"

namespace Lazzo {
	Window::Window(const char* title, int width, int height) {
    const char* glsl_version = "#version 460 core";
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			LZ_ERROR("SDL Couldnt be initialized Error:%s",SDL_GetError());
		}

		if(m_GraphicBackend == GraphicAPI::OpenGL) {
			
			mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
			m_Window = std::unique_ptr<SDL_Window, DeleteWindow>(
				SDL_CreateWindow(title,
					width,
					height,
					SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)
			);
			if (m_Window == nullptr) {
				printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
				return;
			}
      gl_context = SDL_GL_CreateContext(m_Window.get());
			gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
		}
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup scaling
		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(mainScale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
		style.FontScaleDpi = mainScale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

		// Setup Platform/Renderer backends
		ImGui_ImplSDL3_InitForOpenGL(m_Window.get(), gl_context);
		ImGui_ImplOpenGL3_Init(glsl_version);

	}
	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
		SDL_GL_DestroyContext(gl_context);
		SDL_DestroyWindow(m_Window.get());
		SDL_Quit();

	}

	bool Window::OnUpdate() {
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT) {
				return false;
			}
			switch (event.type) {
			case SDL_EVENT_KEY_DOWN:
				KeyDownEvent keyDownEvent(event);
				if (keyDownEvent.ReturnScanCode() == SDL_SCANCODE_ESCAPE) {
					return false;
				}
				LZ_TRACE("Key Down Event: %d", keyDownEvent.ReturnScanCode());
				break;

			}
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

		float f{0.05f};
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(m_Window.get());
		return true;
	}
	GraphicAPI Window::ChooseGraphicBackend() {
    return GraphicAPI::OpenGL;
	}
}