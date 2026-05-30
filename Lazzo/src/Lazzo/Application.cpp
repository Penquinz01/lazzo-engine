#include "lzpch.h"
#include "Application.h"

#include "Lazzo/Log.h"

namespace Lazzo
{
	Application::Application()
	{
		window = std::make_unique<SDLWindow>("Lazzo Engine", 1280, 720);
		running = true;
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		while (running) {
			if (!window->OnUpdate()) {
				running = false;
			}
		}
	}
}