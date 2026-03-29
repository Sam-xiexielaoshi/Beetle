#include <Beetle.h>

class Sandbox : public Beetle::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Beetle::Application*  Beetle::CreateApplication()
{
	return new Sandbox();
}