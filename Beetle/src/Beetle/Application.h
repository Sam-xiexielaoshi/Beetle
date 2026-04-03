#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Beetle/Events/ApplicationEvent.h"
#include "Beetle/LayerStack.h"


namespace Beetle {
	class BEETLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//to be defined in client
	Application* CreateApplication();

}


