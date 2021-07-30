#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	class Texture;

	struct SpriteRendererComponent
	{
		Ref<Texture> texture;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(Ref<Texture> _texture) : texture(_texture) {}

		operator Ref<Texture>() { return texture; }
	};

}