#include <LightEngine.h>

class SandboxLayer : public Light::Layer
{
private:
	std::shared_ptr<Light::Texture> m_AwesomefaceTexture;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> sizes;

	glm::vec2 m_Direction;
	float m_Speed = 1.2f;

	Light::Camera m_Camera;

public:
	SandboxLayer(const std::string& name) 
		: Light::Layer(name), m_Camera(glm::vec2(0.0f), 800.0f / 600.0f, 1.0f), m_Direction(glm::vec2(0.0f, 0.0f))
	{
		Light::ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
		m_AwesomefaceTexture = Light::ResourceManager::GetTexture("awesomeface");

		for (int i = 0; i < 100; i++)
		{
			glm::vec3 position = glm::vec3(-1.0f + (-100.0f / 400.0f) + ((rand() % 1000) / 400.0f), -1.0f + (-100.0f / 300.0f) + ((rand() % 800) / 300.0f), 0.0f);
			glm::vec2 size = glm::vec2(100 / 400.0f, 100 / 300.0f);

			positions.push_back(position);
			sizes.push_back(size);
		}
	}

	void OnRender() override
	{
		m_Camera.CalculateProjection();
		m_Camera.CalculateView();

		Light::Renderer::BeginScene(m_Camera);

		for (int i = 0; i < 100; i++)
			Light::Renderer::DrawQuad(positions[i], sizes[i], m_AwesomefaceTexture);

		Light::Renderer::EndScene();
	}

	bool OnKeyPressed(const Light::KeyPressedEvent& event) override
	{
		if (event.GetKey() == 65) // GLFW_KEY_A
			m_Direction.x +=  -1.0f;
		if(event.GetKey() == 68)  // GLFW_KEY_D
			m_Direction.x += 1.0f;

		if (event.GetKey() == 87) // GLFW_KEY_W
			m_Direction.y +=  1.0f;
		if (event.GetKey() == 83) // GLFW_KEY_S
			m_Direction.y += -1.0f;

		return true;
	}

	bool OnKeyReleased(const Light::KeyReleasedEvent& event) override
	{
		// #todo: add input class
		if (event.GetKey() == 65)  // GLFW_KEY_A
			m_Direction.x -= -1.0f;
		if (event.GetKey() == 68)  // GLFW_KEY_D
			m_Direction.x -= 1.0f;

		if (event.GetKey() == 87) // GLFW_KEY_W
			m_Direction.y -=  1.0f;
		if (event.GetKey() == 83) // GLFW_KEY_S
			m_Direction.y -= -1.0f;

		return true;
	}

	void OnUpdate(float deltaTime) override
	{
		m_Camera.Move(m_Direction * m_Speed * deltaTime);
	}

};
