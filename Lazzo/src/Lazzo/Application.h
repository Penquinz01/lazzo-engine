#pragma once

#include "Core.h"
#include "Window/Window.h"

namespace Lazzo
{
	class LAZZO_API Application {
		public:
		Application();
		~Application();
		void Run();

	private:
		std::unique_ptr<Window> window{};
		bool running = true;
	};
	Application* CreateApplication();
}
