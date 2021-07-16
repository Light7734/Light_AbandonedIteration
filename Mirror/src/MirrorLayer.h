#include <LightEngine.h>

class MirrorLayer : public Light::Layer
{
private:
	std::shared_ptr<Light::Texture> m_AwesomefaceTexture;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> sizes;

	glm::vec2 m_Direction;
	float m_Speed = 1.2f;

	std::shared_ptr<Light::Camera> m_Camera;

	std::shared_ptr<Light::Framebuffer> m_Framebuffer;

public:
	MirrorLayer(const std::string& name)
		: Light::Layer(name), m_Direction(glm::vec2(0.0f, 0.0f))
	{
		m_Camera = std::make_shared<Light::Camera>(glm::vec2(0.0f), 800.0f / 600.0f, 1.0f);

		Light::ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
		m_AwesomefaceTexture = Light::ResourceManager::GetTexture("awesomeface");
		
		m_Framebuffer = std::shared_ptr<Light::Framebuffer>(Light::Framebuffer::Create({ 800u, 600u, 1, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false }, Light::GraphicsContext::GetSharedContext()));

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
		m_Camera->CalculateProjection();
		m_Camera->CalculateView();

		Light::Renderer::BeginScene(m_Camera, m_Framebuffer);

		for (int i = 0; i < 100; i++)
			Light::Renderer::DrawQuad(positions[i], sizes[i], m_AwesomefaceTexture);

		Light::Renderer::EndScene();
	}

	void OnUserInterfaceUpdate()
	{
		ImGui::Begin("GameView");

		static ImVec2 regionAvailPrev = {0, 0};
		ImVec2 regionAvail = ImGui::GetContentRegionAvail();

		if (regionAvail.x != regionAvailPrev.x || regionAvail.y != regionAvailPrev.y)
		{
			m_Framebuffer->Resize({ regionAvail.x, regionAvail.y });
			m_Camera->OnResize({ regionAvail.x, regionAvail.y });
			regionAvailPrev = regionAvail;
		}

		if(Light::GraphicsContext::GetGraphicsAPI() == Light::GraphicsAPI::DirectX)
			ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail);
		else
			ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
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
		m_Camera->Move(m_Direction * m_Speed * deltaTime);
	}

};
