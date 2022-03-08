#include "Entity.hpp"

#include "Scene.hpp"

namespace Light {

Entity::Entity(entt::entity handle, Scene* scene)
    : m_Handle(handle), m_Scene(scene)
{
}

Entity::~Entity()
{
}

} // namespace Light