#pragma once

#include "Base/Base.h"

#include "Scene.h"

#include <entt.hpp>

namespace Light {

	class Entity
	{
	private:
		entt::entity m_Handle;
		Scene* m_Scene;

	public:
		Entity(entt::entity handle = entt::null, Scene* registry = nullptr);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}
	};

}