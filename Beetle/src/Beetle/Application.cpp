#include "Application.h"

#include "Beetle/Events/ApplicationEvent.h"
#include "Beetle/Log.h"

namespace Beetle {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		BT_TRACE(e);

		while (true);
	}
}