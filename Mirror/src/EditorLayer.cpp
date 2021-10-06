#include "EditorLayer.h"

#include "Utility/Serializer.h"

namespace Light {

	EditorLayer::EditorLayer(const std::string& name)
		: Layer(name)
	{
		m_Scene = CreateRef<Scene>();

		m_PropertiesPanel = CreateRef<PropertiesPanel>();
		m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene, m_PropertiesPanel);

		m_Framebuffer = Framebuffer::Create({ 1, 1, 1 }, GraphicsContext::GetSharedContext());
		
		SceneSerializer serializer(m_Scene);
		serializer.Deserialize("../../Mirror/res/Scenes/editorlayer.yaml");

		m_CameraEntity = m_Scene->GetEntityByTag("Game Camera");
	}

	EditorLayer::~EditorLayer()
	{
		SceneSerializer serializer(m_Scene);
		serializer.Serialize("../../Mirror/res/Scenes/editorlayer.yaml");
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
	
}