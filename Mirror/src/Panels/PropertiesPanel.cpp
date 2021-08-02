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

			if(m_EntityContext.HasComponent<CameraComponent>())
			{
				auto& cameraComp = m_EntityContext.GetComponent<CameraComponent>();
				auto& camera = cameraComp.camera;

				SceneCamera::ProjectionType projectionType = camera.GetProjectionType();
				const char* projectionTypesString[] = { "Orthographic", "Perspective" };

				if(ImGui::BeginCombo("ProjectionType", projectionTypesString[(int)projectionType]))
				{
					for(int i = 0; i < 2; i++)
					{
						const bool isSelected = (int)projectionType == i;
						if (ImGui::Selectable(projectionTypesString[i], isSelected))
						{
							projectionType = (SceneCamera::ProjectionType)i;
							camera.SetProjectionType(projectionType);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if(projectionType == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize, nearPlane, farPlane;

					orthoSize = camera.GetOrthographicSize();
					nearPlane = camera.GetOrthographicNearPlane();
					farPlane = camera.GetOrthographicFarPlane();

					if(ImGui::DragFloat("Orthographic Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					if (ImGui::DragFloat("Near Plane", &nearPlane))
						camera.SetOrthographicNearPlane(nearPlane);
					
					if(ImGui::DragFloat("Far Plane", &farPlane))
						camera.SetOrthographicFarPlane(farPlane);
				}

				else // perspective
				{
					float verticalFOV, nearPlane, farPlane;

					verticalFOV = glm::degrees(camera.GetPerspectiveverticalFOV());
					nearPlane = camera.GetPerspectiveNearPlane();
					farPlane = camera.GetPerspectiveFarPlane();

					if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
						camera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));

					if (ImGui::DragFloat("Near Plane", &nearPlane))
						camera.SetPerspectiveNearPlane(nearPlane);

					if (ImGui::DragFloat("Far Plane", &farPlane))
						camera.SetPerspectiveFarPlane(farPlane);
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