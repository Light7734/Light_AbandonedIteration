#pragma once

#include "Panel.h"

#include "Scene/Entity.h"

namespace Light {

	class PropertiesPanel : public Panel
	{
	private:
		Entity m_EntityContext;

	public:
		PropertiesPanel() = default;
		~PropertiesPanel() = default;
		
		void OnUserInterfaceUpdate();

		void SetEntityContext(Entity entity);
	};

}