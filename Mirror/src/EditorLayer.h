#pragma once

#include <LightEngine.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	class EditorLayer : public Layer
	{
	private: 
		// #todo: add camera controller class to the engine
		glm::vec2 m_Direction;
		float m_Speed = 1000.0f;

		Ref<Scene> m_Scene;

		Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
		Ref<PropertiesPanel> m_PropertiesPanel;

		Ref<Framebuffer> m_Framebuffer;

		Entity m_CameraEntity;

		ImVec2 m_AvailableContentRegionPrev;

	public:
		EditorLayer(const std::string& name);

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnUserInterfaceUpdate() override;
	};

}