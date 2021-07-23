#define LIGHT_ENTRY_POINT
#include <LightEngine.h>
#include <EntryPoint.h>

#include "MirrorLayer.h"

class Mirror : public Light::Application
{
public:
	Mirror()
	{
		LT_CLIENT_TRACE("Mirror::Mirror");

		// Set window properties
		Light::WindowProperties properties;
		properties.title = "Mirror";
		properties.size = glm::uvec2(800u, 600u);
		properties.vsync = true;

		m_Window->SetProperties(properties);

		// Attach the sandbox layer
		Light::LayerStack::AttachLayer(new MirrorLayer("MirrorLayer"));
	}
		
	~Mirror()
	{
		LT_CLIENT_TRACE("Mirror::~Mirror");
	}
};

Light::Application* Light::CreateApplication()
{
	return new Mirror();
}