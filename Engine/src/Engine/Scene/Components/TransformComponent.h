#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	struct TransformComponent
	{
		glm::mat4 transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		TransformComponent(const glm::mat4& _transform)
			: transform(_transform)
		{
		}

		operator glm::mat4&() { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

}