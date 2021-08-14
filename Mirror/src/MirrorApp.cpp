#define LIGHT_ENTRY_POINT
#include <LightEngine.h>

#include "EditorLayer.h"

namespace Light {

	class Mirror : public Light::Application
	{
	public:
		Mirror()
		{
			// Set window properties
			Light::WindowProperties properties;
			properties.title = "Mirror";
			properties.size = glm::uvec2(1280u, 720u);
			properties.vsync = true;

			m_Window->SetProperties(properties);

			// Attach the sandbox layer
			LayerStack::EmplaceLayer<EditorLayer>(("MirrorLayer"));
		}
	};

	Application* CreateApplication()
	{
		return new Mirror();
	}

}
