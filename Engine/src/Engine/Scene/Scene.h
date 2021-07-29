#pragma once

#include "Base/Base.h"

#include <entt.hpp>

#include <glm/glm.hpp>

namespace Light {

	class Entity;

	class Scene
	{
	private:
		friend class Entity;
		entt::registry m_Registry;

	public:
		Scene();
		~Scene();

		void OnRender();

		Entity CreateEntity(const std::string& name, const glm::vec2& position, const glm::vec2& size);
	};

}