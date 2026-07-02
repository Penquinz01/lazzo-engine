#include "lzpch.h"
#include "Application.h"

#include "Lazzo/Log.h"

namespace Lazzo
{
	Application::Application()
	{
		window = std::make_unique<Window>("Lazzo Engine", 1280, 720);
		running = true;
        m_LayerStack = LayerStack();
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		window->OnUpdate();
	}
    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

}