#include "Entity.h"

#include "Scene.h"

namespace Light {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_Handle(handle), m_Scene(scene)
	{
	}

	Entity::~Entity()
	{
	}

}