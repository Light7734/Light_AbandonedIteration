#include <LightEngine.h>

#include "SandboxLayer.h"

class Sandbox : public Light::Application
{
public:
	Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::Sandbox");

		Light::LayerStack::AttachLayer(new SandboxLayer("SandboxLayer"));
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