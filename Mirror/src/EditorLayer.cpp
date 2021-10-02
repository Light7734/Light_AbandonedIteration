#include "EditorLayer.h"

namespace Light {

	EditorLayer::EditorLayer(const std::string& name)
		: Layer(name)
	{
		m_Scene = CreateRef<Scene>();

		m_PropertiesPanel = CreateRef<PropertiesPanel>();
		m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene, m_PropertiesPanel);

		SummonAwesomeness();

		m_Framebuffer = Framebuffer::Create({ 1, 1, 1 }, GraphicsContext::GetSharedContext());
		
		m_CameraEntity = m_Scene->CreateEntity("Game Camera", TransformComponent({0.0f, 0.0f, 1000.0f}));
		m_CameraEntity.AddComponent<CameraComponent>(SceneCamera(), true);

		// for native script components
		m_Scene->OnCreate();
	}
	
	void EditorLayer::OnUpdate(float deltaTime)
	{
		m_Scene->OnUpdate(deltaTime);

		m_Direction.x = Input::GetKeyboardKey(Key::A) ? -1.0f :
		                Input::GetKeyboardKey(Key::D) ?  1.0f : 0.0f;
			
		m_Direction.y = Input::GetKeyboardKey(Key::S) ? -1.0f :
		                Input::GetKeyboardKey(Key::W) ?  1.0f : 0.0f;

		auto& cameraTranslation = m_CameraEntity.GetComponent<TransformComponent>().translation;
		cameraTranslation += glm::vec3(m_Direction * m_Speed * deltaTime, 0.0f);

		if (Input::GetKeyboardKey(Key::Escape))
			Application::Quit();
	}
	
	void EditorLayer::OnRender()
	{
		m_Scene->OnRender(m_Framebuffer);
	}
	
	void EditorLayer::OnUserInterfaceUpdate()
	{
		UserInterface::DockspaceBegin();
		ImGui::ShowDemoWindow();

		if (ImGui::Begin("Game"))
		{
			Input::ReceiveGameEvents(ImGui::IsWindowFocused());
			ImVec2 regionAvail = ImGui::GetContentRegionAvail();

			if (m_AvailableContentRegionPrev != regionAvail)
			{
				m_Framebuffer->Resize({ regionAvail.x, regionAvail.y });
				auto& camera = m_CameraEntity.GetComponent<CameraComponent>().camera;
				camera.SetViewportSize(regionAvail.x, regionAvail.y);

				m_AvailableContentRegionPrev = regionAvail;
			}

			if (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX)
				ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail);
			else
				ImGui::Image(m_Framebuffer->GetColorAttachment(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
		} ImGui::End();

		m_SceneHierarchyPanel->OnUserInterfaceUpdate();
		m_PropertiesPanel->OnUserInterfaceUpdate();

		UserInterface::DockspaceEnd();
	}
	
	void EditorLayer::SummonAwesomeness()
	{
		ResourceManager::LoadTexture("awesomeface", "../../Mirror/res/Textures/awesomeface.png");
		auto texture = ResourceManager::GetTexture("awesomeface");

		for(unsigned int i = 0; i < 250; i++)
		{
			const glm::vec3 translation = Math::RandVec3(-500, 500);
			const glm::vec3 scale       = glm::vec3(Math::Rand(125, 200));
			const glm::vec3 rotation    = glm::vec3(0.0f, 0.0f, glm::radians(Math::Rand(0, 359)));

			const glm::vec4 tint        = glm::vec4(Math::RandVec3(0, 1, 2), 1.0f);

			auto entity = m_Scene->CreateEntity("quad" + std::to_string(i), { translation, scale, rotation });
			entity.AddComponent<SpriteRendererComponent>(texture, tint);
		}
	}

}