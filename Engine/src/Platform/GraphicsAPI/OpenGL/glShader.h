#pragma once

#include "Base.h"
#include "Graphics/Shader.h"

namespace Light {

	class glShader : public Shader
	{
	private:
		unsigned int m_ShaderID;

	public:
		glShader(const std::string& vertexPath, const std::string& pixelPath);
		~glShader();

		void Bind() override;
		void UnBind() override;
	};

}