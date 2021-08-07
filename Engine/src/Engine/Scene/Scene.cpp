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

	void Scene::OnCreate()
	{
		/* native scripts */
		{
			m_Registry.view<NativeScriptComponent>().
			each([](NativeScriptComponent& nsc) 
			{
				if (nsc.instance == nullptr)
				{
					nsc.instance = nsc.CreateInstance();
					nsc.instance->OnCreate();
				}
			});
		}
	}

	void Scene::OnUpdate(float deltaTime)
	{
		/* native scripts */
		{
			m_Registry.view<NativeScriptComponent>().
			each([=](NativeScriptComponent& nsc) 
			{
				nsc.instance->OnUpdate(deltaTime);
			});
		}
	}

	void Scene::OnRender(const Ref<Framebuffer>& targetFrameBuffer /* = nullptr */)
	{
		Camera* sceneCamera = nullptr;
		TransformComponent* sceneCameraTransform;

		/* scene camera */
		{
			m_Registry.group(entt::get<TransformComponent, CameraComponent>).
			each([&](TransformComponent& transformComp, CameraComponent& cameraComp)
			{

				if (cameraComp.isPrimary)
				{
					sceneCamera = &cameraComp.camera;
					sceneCameraTransform = &transformComp;
				}
			});
		}

		/* draw quads */
		{
			if (sceneCamera)
			{
				Renderer::BeginScene(sceneCamera, *sceneCameraTransform, targetFrameBuffer);

				m_Registry.group(entt::get<TransformComponent, SpriteRendererComponent>).
				each([](TransformComponent& transformComp, SpriteRendererComponent& spriteRendererComp)
				{
					Renderer::DrawQuad(transformComp, spriteRendererComp.tint, spriteRendererComp.texture);
				});

				Renderer::EndScene();
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& name, const TransformComponent& transform)
	{
		Entity entity { m_Registry.create(), this } ;
		entity.AddComponent<TransformComponent>(transform);

		return entity;
	}

}
