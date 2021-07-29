#define LIGHT_ENTRY_POINT
#include <LightEngine.h>

#include "SandboxLayer.h"

class Sandbox : public Light::Application
{
private:
	 SandboxLayer* m_SandboxLayer;

public:
	Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::Sandbox");

		// Set window properties
		Light::WindowProperties properties;
		properties.title = "Sandbox";
		properties.size = glm::uvec2(800u, 600u);
		properties.vsync = true;

		m_Window->SetProperties(properties);

		// Attach the sandbox layer
		m_SandboxLayer = new SandboxLayer("SandboxLayer");
		Light::LayerStack::AttachLayer(m_SandboxLayer);
	}
		
	~Sandbox()
	{
		LT_CLIENT_TRACE("Sandbox::~Sandbox");
	}
};

Light::Application* Light::CreateApplication()
{
	// note: don't use the logger here, it is not initialized yet
	return new Sandbox();
}