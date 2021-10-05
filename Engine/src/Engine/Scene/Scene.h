#pragma once

#include "Base/Base.h"

#include "Components/TransformComponent.h"

#include <entt/entt.hpp>

#include <glm/glm.hpp>

namespace Light {

	class Entity;

	class Framebuffer;

	class Scene
	{
	private:
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

	private:
		entt::registry m_Registry;

	public:
		Scene();
		~Scene();

		void OnCreate();

		void OnUpdate(float deltaTime);
		void OnRender(const Ref<Framebuffer>& targetFrameBuffer = nullptr);

		Entity CreateEntity(const std::string& name, const TransformComponent& transform = TransformComponent());
	};

}