#include <Beetle.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Beetle::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(Beetle::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f , -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		Beetle::Ref<Beetle::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Beetle::VertexBuffer::Create(vertices, sizeof(vertices)));
		Beetle::BufferLayout layout = {
			{Beetle::ShaderDataType::Float3, "a_Position"},
			{Beetle::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		Beetle::Ref<Beetle::IndexBuffer> indexBuffer;
		indexBuffer.reset(Beetle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Beetle::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f , -0.5f, 0.0f, 0.0f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Beetle::Ref<Beetle::VertexBuffer> squareVB;
		squareVB.reset(Beetle::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Beetle::ShaderDataType::Float3, "a_Position"},
			{Beetle::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2,2,3,0 };
		Beetle::Ref<Beetle::IndexBuffer> squareIB;
		squareIB.reset(Beetle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader=Beetle::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);

		
		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
				
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;


			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
				#version 460 core
			
				layout(location = 0) out vec4 color;

				uniform vec3 u_Color;

				in vec3 v_Position;
			
				void main()
				{
					color = vec4(u_Color, 1.0);
				}
			)";
		m_flatColorShader=Beetle::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture=Beetle::Texture2D::Create("assets/textures/manishHania.png");
		m_BeetleLogo =Beetle::Texture2D::Create("assets/textures/beetle.png");
		

		std::dynamic_pointer_cast<Beetle::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Beetle::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Beetle::TimeStamp ts) override
	{
		//update
		m_CameraController.OnUpdate(ts);

		//render
		Beetle::RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Beetle::RendererCommand::Clear();

		Beetle::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Beetle::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<Beetle::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int i = 0; i < 20; i++) 
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale; 
				Beetle::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Beetle::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_BeetleLogo->Bind();
		Beetle::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//triangle fker
		//Beetle::Renderer::Submit(m_Shader, m_VertexArray);
		
		Beetle::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Beetle::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

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