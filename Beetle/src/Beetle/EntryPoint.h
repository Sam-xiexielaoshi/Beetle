#pragma once
#ifdef BT_PLATFORM_WINDOWS

extern Beetle::Application* Beetle::CreateApplication();

int main(int argc, char** argv)
{
	Beetle::Log::Init();
	BT_CORE_WARN("Initialized Log!");
	int a{ 5 };
	BT_INFO("Hello! Var = {0}", a);


	auto app = Beetle::CreateApplication();
	app->Run();
	delete app;
}

#endif // BT_PLATFORM_WINDOWS
