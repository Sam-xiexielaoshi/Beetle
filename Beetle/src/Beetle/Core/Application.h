#pragma once

#include "Core.h"

#include "Window.h"
#include "Beetle/Core/LayerStack.h"
#include "Beetle/Events/Event.h"
#include "Beetle/Events/ApplicationEvent.h"

#include "Beetle/Core/TimeStamp.h"

#include "Beetle/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Beetle {
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			BT_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};
	class Application
	{
	public:
		Application(const std::string& name = "Hazel App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		static Application& Get() { return *s_Instance; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//to be defined in client
	Application* CreateApplication(ApplicationCommandLineArgs args);

}


