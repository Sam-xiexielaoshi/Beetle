#pragma once

#include "Core.h"

#include "Window.h"
#include "Beetle/Core/LayerStack.h"
#include "Beetle/Events/Event.h"
#include "Beetle/Events/ApplicationEvent.h"

#include "Beetle/Core/TimeStamp.h"

#include "Beetle/ImGui/ImGuiLayer.h"

namespace Beetle {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
		void Close();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		TimeStamp m_TimeStamp;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();

}


