#pragma once

#include "Base.h"

namespace Light {

	class SharedContext;

	class Shader
	{
	public:
		static Shader* Create(const std::string& vertexPath, const std::string& pixelPath, std::shared_ptr<SharedContext> sharedContext);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;

	private:
		static void ExtractShaderSource(std::string& src, const std::string& delim);
	};

}