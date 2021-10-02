#pragma once

#include "Base/Base.h"

#include "Utility/FileManager.h"

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
		static Ref<Shader> Create(BasicFileHandle vertexFile, BasicFileHandle pixelFile, Ref<SharedContext> sharedContext);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}