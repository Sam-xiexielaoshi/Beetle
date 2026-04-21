#include <Beetle.h>
#include "imgui/imgui.h"

class ExampleLayer : public Beetle::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Beetle::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f , -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Beetle::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Beetle::VertexBuffer::Create(vertices, sizeof(vertices)));
		Beetle::BufferLayout layout = {
			{Beetle::ShaderDataType::Float3, "a_Position"},
			{Beetle::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<Beetle::IndexBuffer> indexBuffer;
		indexBuffer.reset(Beetle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Beetle::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.5f , -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<Beetle::VertexBuffer> squareVB;
		squareVB.reset(Beetle::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Beetle::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Beetle::IndexBuffer> squareIB;
		squareIB.reset(Beetle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Beetle::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
				#version 460 core
			
				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;

				out vec3 v_Position;
			
				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				}
			)";

		std::string blueShaderFragmentSrc = R"(
				#version 460 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
			
				void main()
				{
					color = vec4(0.2, 0.3, 0.8, 1.0);
				}
			)";
		m_BlueShader.reset(new Beetle::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{	
			if (Beetle::Input::IsKeyPressed(BT_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMoveSpeed;

			else if (Beetle::Input::IsKeyPressed(BT_KEY_RIGHT))
				m_CameraPosition.x += m_CameraMoveSpeed;

			if (Beetle::Input::IsKeyPressed(BT_KEY_UP))
				m_CameraPosition.y += m_CameraMoveSpeed;

			else if (Beetle::Input::IsKeyPressed(BT_KEY_DOWN))
				m_CameraPosition.y -= m_CameraMoveSpeed;

			if (Beetle::Input::IsKeyPressed(BT_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed;

			else if (Beetle::Input::IsKeyPressed(BT_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed;

		Beetle::RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Beetle::RendererCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Beetle::Renderer::BeginScene(m_Camera);
	
		Beetle::Renderer::Submit(m_BlueShader, m_SquareVA);
		Beetle::Renderer::Submit(m_Shader, m_VertexArray);
		
		Beetle::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Beetle::Event& event) override
	{

	}

private:
	std::shared_ptr<Beetle::Shader> m_Shader;
	std::shared_ptr<Beetle::VertexArray> m_VertexArray;

	std::shared_ptr<Beetle::Shader> m_BlueShader;
	std::shared_ptr<Beetle::VertexArray> m_SquareVA;

	Beetle::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Beetle::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}
	~Sandbox()
	{

	}
};

Beetle::Application*  Beetle::CreateApplication()
{
	return new Sandbox();
}