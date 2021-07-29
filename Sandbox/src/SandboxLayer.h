#include <LightEngine.h>

class SandboxLayer : public Light::Layer
{
private:
	// scene
	Light::Scope<Light::Scene> m_SandboxScene;

	// camera
	Light::Ref<Light::Camera> m_Camera;
	glm::vec2 m_Direction = { 0.0f, 0.0f };
	float m_Speed = 1.2f;

public:
	SandboxLayer(const std::string& name) 
		: Light::Layer(name)
	{
		// initialize scene & camera
		m_SandboxScene = Light::CreateScope<Light::Scene>();
		m_Camera = Light::CreateRef<Light::Camera>(glm::vec2(0.0f), 800.0f / 600.0f, 1.0f);

		// initialize test quads
		Light::ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
		Light::Ref<Light::Texture> awesomeface = Light::ResourceManager::GetTexture("awesomeface");

		for (int i = 0; i < 100; i++)
		{
			glm::vec3 position = glm::vec3(-1.0f + (-100.0f / 400.0f) + ((rand() % 1000) / 400.0f), -1.0f + (-100.0f / 300.0f) + ((rand() % 800) / 300.0f), 0.0f);
			glm::vec2 size = glm::vec2(100 / 400.0f, 100 / 300.0f);

			m_SandboxScene->CreateEntity("awesomeface" + i, position, size).AddComponent<Light::SpriteRendererComponent>(awesomeface);
		}
	}

	void OnRender() override
	{
		Light::Renderer::BeginScene(m_Camera);
		m_SandboxScene->OnRender();
		Light::Renderer::EndScene();
	}

	bool OnKeyPressed(const Light::KeyPressedEvent& event) override
	{
		if (event.GetKey() == Light::Key::A)
			m_Direction.x += -1.0f;
		if(event.GetKey() == Light::Key::D)
			m_Direction.x +=  1.0f;

		if (event.GetKey() == Light::Key::W)
			m_Direction.y +=  1.0f;
		if (event.GetKey() == Light::Key::S)
			m_Direction.y += -1.0f;

		return true;
	}

	bool OnKeyReleased(const Light::KeyReleasedEvent& event) override
	{
		// #todo: add input class
		if (event.GetKey() == Light::Key::A)
			m_Direction.x -= -1.0f;
		if (event.GetKey() == Light::Key::D)
			m_Direction.x -=  1.0f;

		if (event.GetKey() == Light::Key::W)
			m_Direction.y -=  1.0f;
		if (event.GetKey() == Light::Key::S)
			m_Direction.y -= -1.0f;

		return true;
	}

	void OnUpdate(float deltaTime) override
	{
		m_Camera->Move(m_Direction * m_Speed * deltaTime);

		m_Camera->CalculateProjection();
		m_Camera->CalculateView();
	}

};
