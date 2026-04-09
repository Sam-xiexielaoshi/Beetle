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
		if (Beetle::Input::IsKeyPressed(BT_KEY_TAB))
		{
			BT_TRACE("Tab key is pressed (poll)!");
		}
	}

	void OnEvent(Beetle::Event& event) override
	{
		if (event.GetEventType() == Beetle::EventType::KeyPressed)
		{
			Beetle::KeyPressedEvent& e = (Beetle::KeyPressedEvent&)event;
			if(e.GetKeyCode()==BT_KEY_TAB)
				BT_TRACE("Tab key is pressed (event)!");
			BT_TRACE("{0}", (char)e.GetKeyCode());
		}
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