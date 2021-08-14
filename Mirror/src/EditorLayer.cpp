#include "EditorLayer.h"

namespace Light {

	EditorLayer::EditorLayer(const std::string& name)
		: Layer(name), m_Direction(glm::vec2(0.0f, 0.0f))
	{
		m_Scene = CreateRef<Scene>();
		m_PropertiesPanel = CreateRef<PropertiesPanel>();
		m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene, m_PropertiesPanel);
		SummonAwesomeness();

		m_CameraEntity = m_Scene->CreateEntity("Camera", TransformComponent(glm::vec3(0.0f, 0.0f, 1000.0f)));
		m_CameraEntity.AddComponent<CameraComponent>(SceneCamera(), true);

		m_Framebuffer = std::shared_ptr<Framebuffer>(Framebuffer::Create({ 1u, 1u, 1u }, GraphicsContext::GetSharedContext()));


		// for native scripts
		m_Scene->OnCreate();
	}

	void EditorLayer::OnUpdate(float deltaTime)
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
		transform.translation += glm::vec3(m_Direction * m_Speed * deltaTime, 0.0);

		m_Scene->OnUpdate(deltaTime);
	}

	void EditorLayer::OnRender()
	{
		m_Scene->OnRender(m_Framebuffer);
	}

	void EditorLayer::OnUserInterfaceUpdate()
	{
		UserInterface::DockspaceBegin();
		ImGui::ShowDemoWindow();

		if (ImGui::Begin("GameView"))
		{
			Input::ReceiveGameEvents(ImGui::IsWindowFocused());

			ImVec2 regionAvail = ImGui::GetContentRegionAvail();

			if (m_AvailableContentRegionPrev != regionAvail)
			{
				m_AvailableContentRegionPrev = regionAvail;
				m_Framebuffer->Resize({ regionAvail.x, regionAvail.y });

				auto& cameraComp = m_CameraEntity.GetComponent<CameraComponent>();
				cameraComp.camera.SetViewportSize(regionAvail.x, regionAvail.y);
			}

			if (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX)
				ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail);
			else // opengl
				ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
		} ImGui::End();

		m_SceneHierarchyPanel->OnUserInterfaceUpdate();
		m_PropertiesPanel->OnUserInterfaceUpdate();

		UserInterface::DockspaceEnd();
	}

	void EditorLayer::SummonAwesomeness()
	{
		ResourceManager::LoadTexture("awesomeface", "res/Textures/awesomeface.png");
		auto texture = ResourceManager::GetTexture("awesomeface");

		for (int i = 0; i < 420; i++)
		{
			const glm::vec3 translation = Math::RandVec3(-500, 500);
			const glm::vec3 scale = glm::vec3(Math::Rand(250, 350));
			const glm::vec3 rotation = glm::radians(Math::RandVec3(0, 360, 2));;

			Entity quad = m_Scene->CreateEntity("quad" + std::to_string(i), { translation, scale, rotation });
			quad.AddComponent<SpriteRendererComponent>(texture);
		}
	}

}