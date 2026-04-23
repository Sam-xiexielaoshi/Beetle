#include <Beetle.h>
#include <Beetle/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Beetle {
	class BeetleEditor : public Application
	{
	public:
		BeetleEditor() : Application("Beetle Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}
		~BeetleEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new BeetleEditor();
	}
}
