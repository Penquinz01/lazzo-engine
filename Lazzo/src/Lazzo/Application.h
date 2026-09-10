#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Layers/LayerStack.h"
#include "Layers/Layer.h"

namespace Lazzo
{
	class LAZZO_API Application {
		public:
		Application();
		~Application();
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	protected:
		// Scene and UI hooks are called once each frame while the OpenGL context is current.
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	private:
		std::unique_ptr<Window> window{};
		bool running = true;
        LayerStack m_LayerStack;
	};
	Application* CreateApplication();
}
