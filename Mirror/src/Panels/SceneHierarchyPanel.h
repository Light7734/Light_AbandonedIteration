#pragma once

#include "Panel.h"

#include "Base/Base.h"

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Light {

	class SceneHierarchyPanel : public Panel
	{
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Ref<Scene> context);

		void SetContext(Ref<Scene> context);

		void OnUserInterfaceUpdate();

	private:
		void DrawNode(Entity entity, const std::string& label);
	};

}