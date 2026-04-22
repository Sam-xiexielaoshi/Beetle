#include "btpch.h"
#include "Application.h"

#include "Beetle/Renderer/Renderer.h" 

#include "Beetle/Core/Input.h"
#include <GLFW/glfw3.h>


namespace Beetle {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BT_PROFILE_FUNCTION();

		BT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = (Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		BT_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		BT_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		BT_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		//BT_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled()) break;
		}
	}

	void Application::Run()
	{
		BT_PROFILE_FUNCTION();
		while (m_Running)
		{
			BT_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();//platform gettim
			TimeStamp  timestamp = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					BT_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack) layer->OnUpdate(timestamp);
				}
				m_ImGuiLayer->Begin();
				{
					BT_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack) layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}
			
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		BT_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		BT_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}