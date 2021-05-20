#include <LightEngine.h>

class Sandbox : public Light::Application
{
public:
	Sandbox()
	{
	}

};

Light::Application* Light::CreateApplication()
{
	return new Sandbox();
}