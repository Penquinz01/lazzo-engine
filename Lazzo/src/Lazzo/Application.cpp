#include "lzpch.h"
#include "Application.h"

#include "Lazzo/Log.h"

namespace Lazzo
{
	Application::Application()
	{
		window = std::make_unique<Window>("Lazzo Engine", 1280, 720);
		running = true;
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
    window->OnUpdate();
	}
}