#pragma once

#include "Base.h"

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

		//** #TEMP_SHADER_UNIFORMS_TEMP# **//
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

	protected:
		Shader() = default;

	private:
		static void ExtractShaderSource(std::string& src, const std::string& delim);
	};

}