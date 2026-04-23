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

	//rendereeeeeeeeeeee
	Beetle::Renderer2D::ResetStats();
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
		Beetle::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoard, 10.f);
		Beetle::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerBoard, 20.f);
		Beetle::Renderer2D::EndScene();

		Beetle::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			const float step = 0.1f;
			const float quadSize = 0.45f;

			for(float y = -5.0f; y < 5.0f; y += step)
			{
				for(float x = -5.0f; x < 5.0f; x += step)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					Beetle::Renderer2D::DrawQuad({ x, y }, { quadSize, quadSize }, color);
				}
			}
		}
		Beetle::Renderer2D::EndScene();


	}

}

void Sandbox2D::OnImGuiRender()
{
	BT_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	auto stats = Beetle::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Beetle::Event& event)
{
	m_CameraController.OnEvent(event);
}