#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Beetle::Application
{
public:
	Sandbox(const Beetle::ApplicationSpecification& specification)
		: Beetle::Application(specification)
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
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Stag";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}