#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	class SharedContext;

	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& vertexPath, const std::string& pixelPath, Ref<SharedContext> sharedContext);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}