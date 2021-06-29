#include <LightEngine.h>

class SandboxLayer : public Light::Layer
{
private:
	std::shared_ptr<Light::Texture> m_AwesomefaceTexture;

public:
	SandboxLayer(const std::string& name) : Light::Layer(name)
	{
		Light::ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
		m_AwesomefaceTexture = Light::ResourceManager::GetTexture("awesomeface");
	}

	void OnRender() override
	{
		Light::Renderer::DrawQuad(glm::vec3(-0.75f, -0.75f, 0.0f), glm::vec2(0.7f, 0.1f), glm::vec4(1.f, .2f, .2f, 1.0f));
		Light::Renderer::DrawQuad(glm::vec3(0.2f, 0.5f, 0.0f), glm::vec2(0.6f, 0.6f), glm::vec4(.2f, 1.f, .2f, 1.0f));
		Light::Renderer::DrawQuad(glm::vec3(-0.3f, 0.2f, 0.0f), glm::vec2(.4f, .4f), glm::vec4(.2f, 2.f, 1.f, 1.0f));

		Light::Renderer::DrawQuad(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f), m_AwesomefaceTexture);
	}

};
