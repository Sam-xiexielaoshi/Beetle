#pragma once
#ifdef BT_PLATFORM_WINDOWS

extern Beetle::Application* Beetle::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Beetle::CreateApplication();
	app->Run();
	delete app;
}

#endif // BT_PLATFORM_WINDOWS
