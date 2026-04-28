#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Beetle {
	class Stag : public Application
	{
	public:
		Stag(ApplicationCommandLineArgs args) : Application("Stag", args)
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
		return new Stag(args);
	}
}
