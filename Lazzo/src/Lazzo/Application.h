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

	private:
		std::unique_ptr<Window> window{};
		bool running = true;
        LayerStack m_LayerStack;
	};
	Application* CreateApplication();
}
