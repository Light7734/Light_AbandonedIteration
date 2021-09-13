#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	class SharedContext;

	class Shader
	{
	public:
		enum Stage
		{
			NONE = 0,
			VERTEX = 1,
			PIXEL = 2,
			GEOMETRY = 3
		};

	public:
		static Ref<Shader> Create(const std::vector<uint8_t>& vertexBlob, const std::vector<uint8_t>& pixelBlob, const std::string& vertexFileName, const std::string& pixelFileName, Ref<SharedContext> sharedContext);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}