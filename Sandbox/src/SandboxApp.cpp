#include <Beetle.h>

class ExampleLayer : public Beetle::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		BT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Beetle::Event& event) override
	{
		BT_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Beetle::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Beetle::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Beetle::Application*  Beetle::CreateApplication()
{
	return new Sandbox();
}