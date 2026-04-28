#pragma once
#include "Core.h"
#include "Beetle/Core/Application.h"
#ifdef BT_PLATFORM_WINDOWS

extern Beetle::Application* Beetle::CreateApplication(Beetle::ApplicationCommandLineArgs args);
int main(int argc, char** argv)
{
	Beetle::Log::Init();

	BT_PROFILE_BEGIN_SESSION("Startup", "BeetleProfile-Startup.json");
	auto app = Beetle::CreateApplication({argc, argv});
	BT_PROFILE_END_SESSION();

	BT_PROFILE_BEGIN_SESSION("Runtime", "BeetleProfile-Runtime.json");
	app->Run();
	BT_PROFILE_END_SESSION();

	BT_PROFILE_BEGIN_SESSION("Shutdown", "BeetleProfile-Shutdown.json");
	delete app;
	BT_PROFILE_END_SESSION();
}

#endif // BT_PLATFORM_WINDOWS
