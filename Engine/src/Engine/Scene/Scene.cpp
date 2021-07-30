#include "ltpch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"

#include "Graphics/Renderer.h"

#include <glm/glm.hpp>

namespace Light {

	Scene::Scene()
		: m_Registry()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnRender(const Ref<Framebuffer>& targetFrameBuffer /* = nullptr */)
	{
		Camera* sceneCamera = nullptr;
		glm::mat4* sceneCameraTransform;

		/* scene camera */
		{
			auto group = m_Registry.group(entt::get<TransformComponent, CameraComponent>);
			
			for (auto& entity : group)
			{
				auto& [transformComp, cameraComp] = group.get<TransformComponent, CameraComponent>(entity);

				if (cameraComp.isPrimary)
				{
					sceneCamera = &cameraComp.camera;
					sceneCameraTransform = &transformComp.transform;
				}
			}
		}

		/* draw quads */
		{

			if (sceneCamera)
			{
				Renderer::BeginScene(sceneCamera, *sceneCameraTransform, targetFrameBuffer);

				auto group = m_Registry.group(entt::get<TransformComponent, SpriteRendererComponent>);

				for (auto& entity : group)
				{
					auto& [transformComp, spriteRendererComp] = group.get<TransformComponent, SpriteRendererComponent>(entity);
					Renderer::DrawQuad(transformComp.transform, spriteRendererComp.texture);
				}

				Renderer::EndScene();
			}

		}
	}

	Entity Scene::CreateEntity(const std::string& name, const glm::mat4& transform)
	{
		Entity entity { m_Registry.create(), this } ;
		entity.AddComponent<TransformComponent>(transform);

		return entity;
	}

}
