#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Beetle {
	class Stag : public Application
	{
	public:
		Stag(const ApplicationSpecification& spec) : Application(spec)
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}
		~Stag()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Stag";
		spec.CommandLineArgs = args;

		return new Stag(spec);
	}
}
