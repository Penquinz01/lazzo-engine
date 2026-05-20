#pragma once

#include "Core.h"

namespace Lazzo
{
	class LAZZO_API Application {
		public:
		Application();
		~Application();
		void Run();

	};
	Application* CreateApplication();
}
