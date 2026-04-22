#pragma once
#ifdef BT_PLATFORM_WINDOWS

extern Beetle::Application* Beetle::CreateApplication();

int main(int argc, char** argv)
{
	Beetle::Log::Init();

	BT_PROFILE_BEGIN_SESSION("Startup", "BeetleProfile-Startup.json");
	auto app = Beetle::CreateApplication();
	BT_PROFILE_END_SESSION();

	BT_PROFILE_BEGIN_SESSION("Runtime", "BeetleProfile-Runtime.json");
	app->Run();
	BT_PROFILE_END_SESSION();

	BT_PROFILE_BEGIN_SESSION("Shutdown", "BeetleProfile-Shutdown.json");
	delete app;
	BT_PROFILE_END_SESSION();
}

#endif // BT_PLATFORM_WINDOWS
