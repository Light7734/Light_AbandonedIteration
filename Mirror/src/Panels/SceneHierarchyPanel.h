#pragma once

#include "Panel.h"

#include "Base/Base.h"

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Light {

	class PropertiesPanel;

	class SceneHierarchyPanel : public Panel
	{
	private:
		Ref<Scene> m_Context;
		Ref<PropertiesPanel> m_PropertiesPanelContext;
		Entity m_SelectionContext;

	public:
		SceneHierarchyPanel();
		SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel = nullptr);

		void OnUserInterfaceUpdate();

		void SetContext(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel = nullptr);

	private:
		void DrawNode(Entity entity, const std::string& label);
	};

}