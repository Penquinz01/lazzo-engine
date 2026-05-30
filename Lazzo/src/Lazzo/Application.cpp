#include "lzpch.h"
#include "Application.h"

#include "Lazzo/Events/ApplicationEvent.h"
#include "Lazzo/Events/MouseEvent.h"
#include "Lazzo/Log.h"

namespace Lazzo
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LZ_TRACE(e.ToString());

		MouseMovedEvent e2(100, 200);
		LZ_INFO(e2.ToString());

		if (e2.IsInCategory(EventCategoryMouse)) {
			LZ_WARN("e2 is in category Mouse");
		}

		while (true);
	}
}