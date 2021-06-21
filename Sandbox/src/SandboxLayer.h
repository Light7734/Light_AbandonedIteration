#include <LightEngine.h>

class SandboxLayer : public Light::Layer
{
public:
	SandboxLayer(const std::string& name): Light::Layer(name) {}

	void OnRender() override
	{
		Light::Renderer::DrawQuad(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(1.f, 1.f), glm::vec4(1.12f, 1.41f, 1.72f, 1.0f));
		Light::Renderer::DrawQuad(glm::vec3(-0.75f, -0.75f, 0.0f), glm::vec2(0.7f, 0.1f), glm::vec4(1.f, .2f, .2f, 1.0f));
		Light::Renderer::DrawQuad(glm::vec3(0.2f, 0.5f, 0.0f), glm::vec2(0.6f, 0.6f), glm::vec4(.2f, 1.f, .2f, 1.0f));
		Light::Renderer::DrawQuad(glm::vec3(-0.3f, 0.2f, 0.0f), glm::vec2(.4f, .4f), glm::vec4(.2f, 2.f, 1.f, 1.0f));
	}

};
