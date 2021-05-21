#include <LightEngine.h>

class Sandbox : public Light::Application
{
public:
	Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::Sandbox");
	}

	~Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::~Sandbox");
	}
};

Light::Application* Light::CreateApplication()
{
	return new Sandbox();
}