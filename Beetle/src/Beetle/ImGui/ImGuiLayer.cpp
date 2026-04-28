#include "btpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "Beetle/Core/Application.h"
// temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ImGuizmo.h"

namespace Beetle
{

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        BT_PROFILE_FUNCTION();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

        float fontSize = 18.0f;// *2;
        io.Fonts->AddFontFromFileTTF("assets/fonts/Cantarell-Bold.ttf", fontSize);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Cantarell-Regular.ttf", fontSize);

        ImGui::StyleColorsDark();
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetDarkThemeColors();

        Application &app = Application::Get();
        GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        BT_PROFILE_FUNCTION();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event &e)
    {
        if (m_BlockEvents)
        {
            ImGuiIO &io = ImGui::GetIO();
            e.Handled |= e.IsInCategory(EventCategoryMouse) && io.WantCaptureMouse;
            // Keep keyboard events flowing so editor shortcuts still work.
            // e.Handled |= e.IsInCategory(EventCategoryKeyboard) && io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::Begin()
    {
        BT_PROFILE_FUNCTION();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::End()
    {
        BT_PROFILE_FUNCTION();
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
    void ImGuiLayer::SetDarkThemeColors()
    {
        auto &colors = ImGui::GetStyle().Colors;

        // Background
        colors[ImGuiCol_WindowBg] = ImVec4{0.11f, 0.10f, 0.12f, 1.0f};

        // Headers (Tree nodes, collapsing headers)
        colors[ImGuiCol_Header] = ImVec4{0.80f, 0.55f, 0.60f, 0.25f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.95f, 0.60f, 0.65f, 0.80f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.95f, 0.45f, 0.55f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.85f, 0.55f, 0.60f, 0.40f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{1.00f, 0.60f, 0.65f, 0.85f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.95f, 0.40f, 0.50f, 1.0f};

        // Frame BG (input fields, sliders)
        colors[ImGuiCol_FrameBg] = ImVec4{0.20f, 0.18f, 0.22f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.85f, 0.55f, 0.60f, 0.60f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.95f, 0.45f, 0.55f, 0.90f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.18f, 0.16f, 0.20f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.95f, 0.60f, 0.65f, 0.80f};
        colors[ImGuiCol_TabActive] = ImVec4{0.85f, 0.45f, 0.55f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.14f, 0.13f, 0.16f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.20f, 0.18f, 0.22f, 1.0f};

        // Title bar
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.13f, 0.17f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.20f, 0.16f, 0.22f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.10f, 0.09f, 0.12f, 1.0f};

        // Accent (important!)
        colors[ImGuiCol_CheckMark] = ImVec4{1.00f, 0.60f, 0.70f, 1.0f};
        colors[ImGuiCol_SliderGrab] = ImVec4{0.95f, 0.55f, 0.65f, 1.0f};
        colors[ImGuiCol_SliderGrabActive] = ImVec4{1.00f, 0.45f, 0.60f, 1.0f};

        // Borders
        colors[ImGuiCol_Border] = ImVec4{0.30f, 0.25f, 0.30f, 0.50f};

        // Resize grip
        colors[ImGuiCol_ResizeGrip] = ImVec4{0.95f, 0.55f, 0.65f, 0.30f};
        colors[ImGuiCol_ResizeGripHovered] = ImVec4{1.00f, 0.60f, 0.70f, 0.80f};
        colors[ImGuiCol_ResizeGripActive] = ImVec4{1.00f, 0.50f, 0.60f, 1.0f};
    }
}