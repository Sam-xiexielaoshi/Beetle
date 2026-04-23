#pragma once
#include "Beetle.h"

#include "ParticleSystem.h"

class Sandbox2D : public Beetle::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Beetle::TimeStamp ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Beetle::Event& event) override;

private:
	Beetle::OrthographicCameraController m_CameraController;

	//temp
	Beetle::Ref<Beetle::VertexArray> m_SquareVA;
	Beetle::Ref<Beetle::Shader> m_flatColorShader;
	Beetle::Ref<Beetle::FrameBuffer> m_FrameBuffer;

	Beetle::Ref<Beetle::Texture2D> m_CheckerBoard;


	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};