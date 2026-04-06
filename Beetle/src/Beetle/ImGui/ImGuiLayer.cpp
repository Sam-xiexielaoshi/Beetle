//#include "btpch.h"
//#include "ImGuiLayer.h"
//#include "imgui.h"
//#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
//#include "GLFW/glfw3.h"
//namespace Beetle {
//	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
//	{
//	}
//	ImGuiLayer::~ImGuiLayer()
//	{
//	}
//
//	void ImGuiLayer::OnAttach()
//	{
//		ImGui::CreateContext();
//		ImGui::StyleColorsDark();
//
//		ImGuiIO& io = ImGui::GetIO();
//		io.BackendFlags = ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;
//		
//        
//	}
//
//	void ImGuiLayer::OnDetach()
//	{
//	}
//
//	void ImGuiLayer::OnUpdate()
//	{
//	}
//	void ImGuiLayer::OnEvent(Event& event)
//	{
//	}
//}
#include "btpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Beetle/Application.h"
 //temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Beetle {

    //this is a temporary fix eventully will be replaced by the beetle key codes and input system
    static ImGuiKey GLFWKeyToImGuiKey(int key)
    {
        switch (key)
        {
        case GLFW_KEY_TAB: return ImGuiKey_Tab;
        case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
        case GLFW_KEY_UP: return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
        case GLFW_KEY_HOME: return ImGuiKey_Home;
        case GLFW_KEY_END: return ImGuiKey_End;
        case GLFW_KEY_INSERT: return ImGuiKey_Insert;
        case GLFW_KEY_DELETE: return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE: return ImGuiKey_Space;
        case GLFW_KEY_ENTER: return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;

        case GLFW_KEY_A: return ImGuiKey_A;
        case GLFW_KEY_C: return ImGuiKey_C;
        case GLFW_KEY_V: return ImGuiKey_V;
        case GLFW_KEY_X: return ImGuiKey_X;
        case GLFW_KEY_Y: return ImGuiKey_Y;
        case GLFW_KEY_Z: return ImGuiKey_Z;

        default: return ImGuiKey_None;
        }
    }

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
		ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get(); 
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
		ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void ImGuiLayer::OnEvent(Event& event)
    {
		EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        //dispatcher.Dispatch<KeyTypedEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BEETLE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
        
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos=ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        //io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();
		return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
    {
        //ImGuiIO& io = ImGui::GetIO();
        /*ImGuiKey key = GLFWKeyToImGuiKey(event.GetKeyCode());
        if (key != ImGuiKey_None)
            io.AddKeyEvent(key, true);*/
        return false;

    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
    {
        //ImGuiIO& io = ImGui::GetIO();
        /*ImGuiKey key = GLFWKeyToImGuiKey(event.GetKeyCode());
        if (key != ImGuiKey_None)
            io.AddKeyEvent(key, false);*/
        return false;

    }

    /*bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter((unsigned int)event.GetKeyCode());
        return false;

    }*/

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)event.GetWidth(), (float)event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return false;

    }

}