#include "ltpch.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "Graphics/Renderer.h"

#include <glm/glm.hpp>

namespace Light {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnRender()
	{
		auto group = m_Registry.group(entt::get<TransformComponent, SpriteRendererComponent>);

		group.each([](TransformComponent& transform, SpriteRendererComponent& sprite) {
			Renderer::DrawQuad(glm::vec3(transform.position, 0.0f), transform.size, sprite.texture);
		});

	}

	Entity Scene::CreateEntity(const std::string& name, const glm::vec2& position, const glm::vec2& size)
	{
		Entity entity { m_Registry.create(), this } ;
		entity.AddComponent<TransformComponent>(position, size);

		return entity;

	}

}
