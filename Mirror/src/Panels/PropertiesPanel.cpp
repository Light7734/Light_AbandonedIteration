#include "PropertiesPanel.h"

#include "Scene/Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>


namespace Light {
	
	void PropertiesPanel::OnUserInterfaceUpdate()
	{
		ImGui::Begin("Properties");

		if(m_EntityContext.IsValid())
		{
			if(m_EntityContext.HasComponent<TagComponent>())
			{
				auto& tagComponent = m_EntityContext.GetComponent<TagComponent>();

				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				std::strncpy(buffer, tagComponent.tag.c_str(), sizeof(buffer));
				if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				{
					LT_ENGINE_TRACE("bruh");
					tagComponent.tag = std::string(buffer);
				}
			}

			if(m_EntityContext.HasComponent<TransformComponent>())
			{

				if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
				{
					auto& transformComponent = m_EntityContext.GetComponent<TransformComponent>();
					ImGui::DragFloat3("Position", glm::value_ptr(transformComponent.transform[3]), 0.5f);

					ImGui::TreePop();
				}
			}
		}

		ImGui::End();
	}

	void PropertiesPanel::SetEntityContext(Entity entity)
	{
		m_EntityContext = entity;
	}

}