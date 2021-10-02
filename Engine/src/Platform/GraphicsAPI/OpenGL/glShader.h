#pragma once

#include "Graphics/Shader.h"

#include "Base/Base.h"

#include "Utility/FileManager.h"

#include <ShaderConductor/ShaderConductor.hpp>

namespace Light {

	class glShader : public Shader
	{
	private:
		unsigned int m_ShaderID;

	public:
		glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile);
		~glShader();

		void Bind() override;
		void UnBind() override;

	private:
		ShaderConductor::Compiler::ResultDesc CompileHLSL(BasicFileHandle file, Shader::Stage stage);

		unsigned int CompileShader(const std::string& source, Shader::Stage stage);
	};

}