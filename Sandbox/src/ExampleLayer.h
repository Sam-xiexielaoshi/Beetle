#pragma once
#include "Beetle.h"

class ExampleLayer : public Beetle::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Beetle::TimeStamp ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Beetle::Event& event) override;

private:
	Beetle::ShaderLibrary m_ShaderLibrary;
	Beetle::Ref<Beetle::Shader> m_Shader;
	Beetle::Ref<Beetle::VertexArray> m_VertexArray;

	Beetle::Ref<Beetle::Shader> m_flatColorShader;
	Beetle::Ref<Beetle::VertexArray> m_SquareVA;

	Beetle::Ref<Beetle::Texture2D> m_Texture, m_BeetleLogo;

	Beetle::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};