#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Beetle::Application
{
public:
	Sandbox(Beetle::ApplicationCommandLineArgs args)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Beetle::Application*  Beetle::CreateApplication(Beetle::ApplicationCommandLineArgs args)
{
	return new Sandbox(args);
}