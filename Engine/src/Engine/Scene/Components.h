#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	class Texture;

	// #todo: store a mat4 for transform
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
		Ref<Texture> texture;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(Ref<Texture> _texture) : texture(_texture) {}

		operator Ref<Texture>() { return texture; }
	};

}