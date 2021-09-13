#pragma once

#include "Graphics/Shader.h"

#include "Base/Base.h"

#include <ShaderConductor/ShaderConductor.hpp>

namespace Light {

	class glShader : public Shader
	{
	private:
		unsigned int m_ShaderID;

	public:
		glShader(const std::vector<uint8_t>& vertexBlob, const std::vector<uint8_t>& pixelBlob, const std::string& vertexFileName, const std::string& pixelFileName);
		~glShader();

		void Bind() override;
		void UnBind() override;

	private:
		ShaderConductor::Compiler::ResultDesc CompileHLSL(std::vector<uint8_t> blob, std::string fileName, Shader::Stage stage);

		unsigned int CompileShader(const std::string& source, Shader::Stage stage);
	};

}