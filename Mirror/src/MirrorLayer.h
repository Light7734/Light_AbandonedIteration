#include <LightEngine.h>

namespace Light {

	class MirrorLayer : public Layer
	{
	private:
		std::shared_ptr<Texture> m_AwesomefaceTexture;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> sizes;

		glm::vec2 m_Direction;
		float m_Speed = 1000.0f;

		Ref<Camera> m_Camera;

		Ref<Framebuffer> m_Framebuffer;

		Scene m_Scene;

		Entity m_TestEntity;

		bool m_GameSceneEvents = false;

	public:
		MirrorLayer(const std::string& name)
			: Layer(name), m_Direction(glm::vec2(0.0f, 0.0f))
		{
			m_Camera = std::make_shared<Camera>(glm::vec2(500.0f), NULL, 1000.0f);

			ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
			m_AwesomefaceTexture = ResourceManager::GetTexture("awesomeface");

			m_Framebuffer = std::shared_ptr<Framebuffer>(Framebuffer::Create({ 800u, 600u, 1, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false }, GraphicsContext::GetSharedContext()));

			for (int i = 0; i < 250; i++)
			{
				glm::vec3 position = glm::vec3(rand() % 3000 - 1400.0f, rand() % 3000 - 1400.0f, 0.0f);
				glm::vec2 size = glm::vec2(250.0f, 250.0f);

				positions.push_back(position);
				sizes.push_back(size);

				m_Scene.CreateEntity("quad", position, size).AddComponent<SpriteRendererComponent>(m_AwesomefaceTexture);
			}
		}

		void OnRender() override
		{
			m_Camera->CalculateProjection();
			m_Camera->CalculateView();

			Renderer::BeginScene(m_Camera, m_Framebuffer);

			m_Scene.OnRender();

			Renderer::EndScene();
		}

		void OnUserInterfaceUpdate()
		{
			if (ImGui::Begin("GameView"))
			{
				Input::ReceiveGameEvents(ImGui::IsWindowFocused());

				static ImVec2 regionAvailPrev = { 0, 0 };
				ImVec2 regionAvail = ImGui::GetContentRegionAvail();

				if (regionAvail.x != regionAvailPrev.x || regionAvail.y != regionAvailPrev.y)
				{
					m_Framebuffer->Resize({ regionAvail.x, regionAvail.y });
					m_Camera->OnResize({ regionAvail.x, regionAvail.y });
					regionAvailPrev = regionAvail;
				}

				if (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX)
					ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail);
				else
					ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
			}

			ImGui::End();
		}

		void OnUpdate(float deltaTime) override
		{
			if (Input::GetKeyboardKey(KEY_A))
				m_Direction.x = -1.0f;
			else if (Input::GetKeyboardKey(KEY_D))
				m_Direction.x = 1.0f;
			else
				m_Direction.x = 0.0f;

			if (Input::GetKeyboardKey(KEY_W))
				m_Direction.y = 1.0f;
			else if (Input::GetKeyboardKey(KEY_S))
				m_Direction.y = -1.0f;
			else
				m_Direction.y = 0.0f;

			m_Camera->Move(m_Direction * m_Speed * deltaTime);
		}

	};

}