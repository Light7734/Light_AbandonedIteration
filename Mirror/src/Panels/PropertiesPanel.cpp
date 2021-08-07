#include "PropertiesPanel.h"

#include "Scene/Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_internal.h>

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
					auto& transform = m_EntityContext.GetComponent<TransformComponent>();

					DrawVec3Control("Translation", transform.translation);

					ImGui::TreePop();
				}
			}

			if (m_EntityContext.HasComponent<SpriteRendererComponent>())
			{
				if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite"))
				{
					auto& spriteRenderer = m_EntityContext.GetComponent<SpriteRendererComponent>();
					ImGui::ColorEdit4("Color", &spriteRenderer.tint[0]);

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

	void PropertiesPanel::DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue /*= 0.0f*/, float columnWidth /*= 100.0f*/)
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0  });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		if (ImGui::Button("Z", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
	}

}