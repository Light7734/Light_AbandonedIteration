#define LIGHT_ENTRY_POINT
#include "EditorLayer.hpp"

#include <LightEngine.hpp>

namespace Light {

class Mirror: public Light::Application
{
public:
	Mirror(std::string execName, std::vector<std::string> args)
	    : Application(execName, args)
	{
		// Set window properties
		Light::WindowProperties properties;
		properties.title = "Mirror";
		properties.size  = glm::uvec2(1280u, 720u);
		properties.vsync = true;

		m_Window->SetProperties(properties);

		// Attach the sandbox layer
		LayerStack::EmplaceLayer<EditorLayer>(("MirrorLayer"), args);
	}
};

Application* CreateApplication(std::string execName, std::vector<std::string> args)
{
	return new Mirror(execName, args);
}

} // namespace Light
