#pragma once

#include "Base.h"

#include <entt.hpp>

namespace Light {

	class Scene;

	class Entity
	{
	private:
		entt::entity m_Handle;
		Scene* m_Scene;

	public:
		Entity(){}
		Entity(entt::entity handle, Scene* registry);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

	};

}