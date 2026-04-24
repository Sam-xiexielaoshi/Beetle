#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Beetle {
	class Stag : public Application
	{
	public:
		Stag() : Application("Stag")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}
		~Stag()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Stag();
	}
}
