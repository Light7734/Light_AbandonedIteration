#include "SceneHierarchyPanel.h"

#include "Scene/Components.h"

#include <entt.hpp>

#include <imgui.h>

namespace Light {

	SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene> context)
		: m_Context(context)
	{
	}

	void SceneHierarchyPanel::SetContext(Ref<Scene> context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnUserInterfaceUpdate()
	{
		ImGui::Begin("Hierarchy");

		m_Context->m_Registry.
		each([&](auto& entityID)
		{
			Entity entity(entityID, m_Context.get());
			const std::string& tag = entity.GetComponent<TagComponent>();

			DrawNode(entity, tag);
		});

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawNode(Entity entity, const std::string& label)
	{
		ImGuiTreeNodeFlags flags = (m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : NULL) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

		bool expanded = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity), flags, label.c_str());

		if (ImGui::IsItemClicked())
			m_SelectionContext = entity;

		if(expanded)
		{
			ImGui::Text("TEST_OPENED_TREE!");
			ImGui::TreePop();
		}
	}

}