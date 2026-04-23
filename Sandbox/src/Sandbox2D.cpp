#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	BT_PROFILE_FUNCTION();
	m_CheckerBoard = Beetle::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	BT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Beetle::TimeStamp ts)
{
	{
		BT_PROFILE_FUNCTION("Sandbox2D::OnUpdate");
	}

	//update
	{
		m_CameraController.OnUpdate(ts);
	}

	//render
	{
		BT_PROFILE_SCOPE("Renderer Prep");
		Beetle::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Beetle::RendererCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		BT_PROFILE_SCOPE("Renderer Draw");
		Beetle::Renderer2D::BeginScene(m_CameraController.GetCamera());		
		Beetle::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, { 0.8f, 0.8f }, 45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
		Beetle::Renderer2D::DrawQuad({ -1.0f, 0.0f}, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Beetle::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Beetle::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoard, 10.f);
		Beetle::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerBoard, 20.f);
		Beetle::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	BT_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Beetle::Event& event)
{
	m_CameraController.OnEvent(event);
}