#pragma once

#include "Panels/AssetBrowser.hpp"
#include "Panels/PropertiesPanel.hpp"
#include "Panels/SceneHierarchyPanel.hpp"

#include <LightEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

class EditorLayer: public Layer
{
private:
	std::string m_SceneDir;

	// #todo: add camera controller class to the engine
	glm::vec2 m_Direction;
	float m_Speed = 1000.0f;

	Ref<Scene> m_Scene;

	Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
	Ref<PropertiesPanel> m_PropertiesPanel;
	Ref<AssetBrowserPanel> m_ContentBrowserPanel;

	Ref<Framebuffer> m_Framebuffer;

	Entity m_CameraEntity;

	ImVec2 m_AvailableContentRegionPrev;

public:
	EditorLayer(const std::string& name, const std::vector<std::string>& args);
	~EditorLayer();

	void OnUpdate(float deltaTime) override;

	void OnRender() override;

	void OnUserInterfaceUpdate() override;
};

} // namespace Light
