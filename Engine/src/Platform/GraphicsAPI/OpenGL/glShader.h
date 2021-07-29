#pragma once

#include "Graphics/Shader.h"

#include "Base/Base.h"

namespace Light {

	class glShader : public Shader
	{
	private:
		unsigned int m_ShaderID;

	public:
		glShader(const std::string& vetexSource, const std::string& fragmentSource);
		~glShader();

		void Bind() override;
		void UnBind() override;
	};

}