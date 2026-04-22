#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "Sandbox2D.h"


class Sandbox : public Beetle::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Beetle::Application*  Beetle::CreateApplication()
{
	return new Sandbox();
}