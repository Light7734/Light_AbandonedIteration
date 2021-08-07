#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	struct TransformComponent
	{
		glm::vec3 translation;
		glm::vec3 scale;
		glm::vec3 rotation;

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(const glm::vec3& _translation = glm::vec3(0.0f, 0.0f, 0.0f),
		                   const glm::vec3& _scale = glm::vec3(1.0f, 1.0f, 1.0f),
		                   const glm::vec3& _rotation = glm::vec3(0.0f, 0.0f, 0.0f))

			: translation(_translation),
			  scale(_scale),
			  rotation(_rotation)
		{
		}

		const glm::mat4& GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), translation)                          *

			       glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
			       glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
			       glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *

			       glm::scale(glm::mat4(1.0f), scale);
		}

		operator const glm::mat4& () const { return GetTransform(); }
	};

}