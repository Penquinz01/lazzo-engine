#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Layers/LayerStack.h"
#include "Layers/Layer.h"
#include <string>
#include <vector>

namespace Lazzo
{
	class LAZZO_API Application {
		public:
Application();
		virtual ~Application() = default;
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *window; }

	protected:
		// Scene and UI hooks are called once each frame while the OpenGL context is current.
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

		void BeginRightPanel(float width = 300.0f);
		void EndRightPanel();

		// Inspector helpers (ImGui lives in the DLL, so clients compose
		// selection UI through these instead of calling ImGui directly).
		void InspectorSelectableList(const std::vector<std::string>& names, int& selectedIndex);
		void InspectorEmptyHint();
		void InspectorTitle(const char* text);
		bool IsUIMouseCaptured() const;

	private:
		std::unique_ptr<Window> window{};
		bool running = true;
        LayerStack m_LayerStack;
	};
	Application* CreateApplication();
}
