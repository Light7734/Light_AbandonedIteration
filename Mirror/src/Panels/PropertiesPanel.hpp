#pragma once

#include "Panel.hpp"
#include "Scene/Entity.hpp"

namespace Light {

class PropertiesPanel: public Panel
{
private:
	Entity m_EntityContext;

public:
	PropertiesPanel()  = default;
	~PropertiesPanel() = default;

	void OnUserInterfaceUpdate();

	void SetEntityContext(Entity entity);

private:
	void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

	template<typename ComponentType, typename UIFunction>
	void DrawComponent(const std::string& name, Entity entity, UIFunction function);
};


} // namespace Light
