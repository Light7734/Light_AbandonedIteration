#pragma once

#include "Base/Base.h"

#include <entt.hpp>

#include <glm/glm.hpp>

namespace Light {

	class Entity;

	class Framebuffer;

	class Scene
	{
		friend class Entity;
		friend class SceneHierarchyPanel;
	private:
		entt::registry m_Registry;

	public:
		Scene();
		~Scene();

		void OnCreate();

		void OnUpdate(float deltaTime);
		void OnRender(const Ref<Framebuffer>& targetFrameBuffer = nullptr);

		Entity CreateEntity(const std::string& name, const glm::mat4& transform);
	};

}