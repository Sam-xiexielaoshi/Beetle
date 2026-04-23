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
	m_SpriteSheet = Beetle::Texture2D::Create("assets/game/texture/RPGpack_sheet_2X.png");

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
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
#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		BT_PROFILE_SCOPE("Renderer Draw");
		Beetle::Renderer2D::BeginScene(m_CameraController.GetCamera());		
		Beetle::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Beetle::Renderer2D::DrawQuad({ -1.0f, 0.0f}, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Beetle::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Beetle::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoard, 10.f);
		Beetle::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerBoard, 20.f);
		Beetle::Renderer2D::EndScene();

		Beetle::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			const float step = 0.5f;
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
#endif

	if (Beetle::Input::IsMouseButtonPressed(BT_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Beetle::Input::GetMousePosition();
		auto width = Beetle::Application::Get().GetWindow().GetWidth();
		auto height = Beetle::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	Beetle::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Beetle::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SpriteSheet);
	Beetle::Renderer2D::EndScene();



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