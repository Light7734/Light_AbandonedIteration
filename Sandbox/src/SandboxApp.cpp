#define LIGHT_ENTRY_POINT
#include <LightEngine.h>

#include "SandboxLayer.h"

class Sandbox : public Light::Application
{
public:
	Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::Sandbox");

		// Set window properties
		Light::WindowProperties properties;
		properties.title = "Sandbox";
		properties.width = 800u;
		properties.height = 600u;
		properties.vsync = true;

		m_Window->SetProperties(properties);

		// Attach the sandbox layer
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