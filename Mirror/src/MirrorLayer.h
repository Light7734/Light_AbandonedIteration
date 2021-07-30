#include <LightEngine.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	class MirrorLayer : public Layer
	{
	private:
		Ref<Texture> m_AwesomefaceTexture;

		glm::vec2 m_Direction;
		float m_Speed = 1000.0f;

		Ref<Framebuffer> m_Framebuffer;

		Scene m_Scene;
		Entity m_CameraEntity;

	public:
		MirrorLayer(const std::string& name)
			: Layer(name), m_Direction(glm::vec2(0.0f, 0.0f))
		{
			ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
			m_AwesomefaceTexture = ResourceManager::GetTexture("awesomeface");

			m_Framebuffer = std::shared_ptr<Framebuffer>(Framebuffer::Create({ 800u, 600u, 1, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }, GraphicsContext::GetSharedContext()));

			m_CameraEntity = m_Scene.CreateEntity("camera", glm::mat4(1.0f));
			m_CameraEntity.AddComponent<CameraComponent>(SceneCamera(), true);

			for (int i = 0; i < 250; i++)
			{
				glm::vec3 position = glm::vec3(rand() % 3000 - 1400.0f, rand() % 3000 - 1400.0f, 0.0f);
				glm::vec2 size = glm::vec2(250.0f, 250.0f);

				m_Scene.CreateEntity("quad", glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
				                             glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f})).AddComponent<SpriteRendererComponent>(m_AwesomefaceTexture);
			}
		}

		void OnRender() override
		{
			m_Scene.OnRender(m_Framebuffer);
		}

		void OnUserInterfaceUpdate()
		{
			if (ImGui::Begin("GameView"))
			{
				// #todo: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
				Input::ReceiveGameEvents(ImGui::IsWindowFocused());

				static ImVec2 regionAvailPrev = { 0, 0 };
				ImVec2 regionAvail = ImGui::GetContentRegionAvail();

				if (regionAvail.x != regionAvailPrev.x || regionAvail.y != regionAvailPrev.y)
				{
					m_Framebuffer->Resize({ regionAvail.x, regionAvail.y });

					auto& cameraComp = m_CameraEntity.GetComponent<CameraComponent>();
					cameraComp.camera.SetViewportSize(regionAvail.x, regionAvail.y);

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
			if (Input::GetKeyboardKey(Key::A))
				m_Direction.x = -1.0f;
			else if (Input::GetKeyboardKey(Key::D))
				m_Direction.x = 1.0f;
			else
				m_Direction.x = 0.0f;

			if (Input::GetKeyboardKey(Key::W))
				m_Direction.y = 1.0f;
			else if (Input::GetKeyboardKey(Key::S))
				m_Direction.y = -1.0f;
			else
				m_Direction.y = 0.0f;
			
			auto& transform = m_CameraEntity.GetComponent<TransformComponent>();
			transform = glm::translate(transform.transform, glm::vec3(m_Direction * m_Speed * deltaTime, 0.0));
		}

	};

}