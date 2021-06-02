#pragma once

#include "Base.h"

namespace Light {

	class Shader
	{
	public:
		static Shader* Create(const std::string& vertexPath, const std::string& pixelPath, void* sharedContext);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}