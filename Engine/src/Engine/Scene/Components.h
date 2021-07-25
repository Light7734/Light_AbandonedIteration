#pragma once

#include "Base.h"

#include <glm/glm.hpp>

namespace Light {

	class Texture;

	struct TransformComponent
	{
		glm::vec2 position, size;

		// glm::mat4 transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec2& _position, const glm::vec2& _size) : position(_position), size(_size) {}

		// operator glm::mat4&() { return transform; }
		// operator const glm::mat4& () const { return transform; }
	};

	struct SpriteRendererComponent
	{
		std::shared_ptr<Texture> texture;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(std::shared_ptr<Texture> _texture) : texture(_texture) {}

		operator std::shared_ptr<Texture>() { return texture; }
	};

}