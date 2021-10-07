#include "glShader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Light {

	glShader::glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile):
		m_ShaderID(NULL)
	{
		// create
		m_ShaderID = glCreateProgram();

		// compile hlsl to glsl
		ShaderConductor::Compiler::ResultDesc vertexResult = CompileHLSL(vertexFile, Shader::Stage::VERTEX);
		ShaderConductor::Compiler::ResultDesc pixelResult = CompileHLSL(pixelFile, Shader::Stage::PIXEL);

		LT_ENGINE_ASSERT(!vertexResult.hasError, "glShader::glShader: failed to compile hlsl vertex shader: {}", vertexFile.GetPath());
		LT_ENGINE_ASSERT(!pixelResult.hasError, "glShader::glShader: failed to compile hlsl pixel shader: {}", pixelFile.GetPath());

		// extract glsl source
		std::string vertexSource = std::string(reinterpret_cast<const char*>(vertexResult.target.Data()));
		vertexSource.resize(vertexResult.target.Size());

		std::string pixelSource = std::string(reinterpret_cast<const char*>(pixelResult.target.Data()));
		pixelSource.resize(pixelResult.target.Size());

		// compile glsl
		unsigned int vertexShader = CompileShader(vertexSource, Shader::Stage::VERTEX);
		unsigned int pixelShader = CompileShader(pixelSource, Shader::Stage::PIXEL);

		// attach shaders
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, pixelShader);
		
		// link shader program
		glLinkProgram(m_ShaderID);
		
		// delete shaders (free memory)
		glDeleteShader(vertexShader);
		glDeleteShader(pixelShader);
	}

	glShader::~glShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void glShader::Bind()
	{
		glUseProgram(m_ShaderID);
	}

	void glShader::UnBind()
	{
		glUseProgram(NULL);
	}

	ShaderConductor::Compiler::ResultDesc glShader::CompileHLSL(BasicFileHandle file, Shader::Stage stage)
	{
		// check
		LT_ENGINE_ASSERT(file.IsValid(), "glShader::CompileHLSL: invalid 'file'");
		LT_ENGINE_ASSERT(stage, "glShader::CompileHLSL: invalid 'stage': None");

		// compiler options
		ShaderConductor::Compiler::Options options = {};
		options.packMatricesInRowMajor = true;
		options.enableDebugInfo = true;
		options.disableOptimizations = true;
		options.inheritCombinedSamplerBindings = true;
		options.shaderModel = { 4, 5 };

		// compiler target descriptor
		ShaderConductor::Compiler::TargetDesc targetDesc = {};
		targetDesc.language = ShaderConductor::ShadingLanguage::Glsl;
		targetDesc.version = "440 core";
		targetDesc.asModule = false;

		// compiler source descriptor
		ShaderConductor::Compiler::SourceDesc sourceDesc = {};
		std::string source = std::string(reinterpret_cast<char*>(file.GetData()), file.GetSize());
		sourceDesc.source = source.c_str();
		sourceDesc.fileName = file.GetName().c_str();
		sourceDesc.entryPoint = "main";
		sourceDesc.stage = stage == Shader::Stage::VERTEX ? ShaderConductor::ShaderStage::VertexShader :
		                   stage == Shader::Stage::PIXEL  ? ShaderConductor::ShaderStage::PixelShader  :
		                                                    ShaderConductor::ShaderStage::GeometryShader;
		sourceDesc.defines = nullptr;
		sourceDesc.numDefines = 0u;
		sourceDesc.loadIncludeCallback = nullptr;

		// compilation result
		ShaderConductor::Compiler::ResultDesc result = ShaderConductor::Compiler::Compile(sourceDesc, options, targetDesc);

		// log error/warning
		if (result.errorWarningMsg.Size() != 0u)
		{
			const char* errorWarningStr = reinterpret_cast<const char*>(result.errorWarningMsg.Data());
			
			if(result.hasError)
				LT_ENGINE_ERROR("glShader::CompileHLSL: ShaderConductor error:'{}': {}", file.GetName(), errorWarningStr);
			else 
				LT_ENGINE_WARN("glShader::CompileHLSL: ShaderConductor warning:'{}': {}", errorWarningStr);
		}
		
		return result;
	}

	unsigned int glShader::CompileShader(const std::string& source, Shader::Stage stage)
	{
		// &(address of) needs an lvalue
		const char* lvalue_source = reinterpret_cast<const char*>(source.c_str());
		unsigned int shader = glCreateShader(stage == Shader::Stage::VERTEX   ? GL_VERTEX_SHADER   :
		                                     stage == Shader::Stage::PIXEL    ? GL_FRAGMENT_SHADER :
		                                     stage == Shader::Stage::GEOMETRY ? GL_GEOMETRY_SHADER :
		                                                                        NULL);

		// compile
		glShaderSource(shader, 1, &lvalue_source, NULL);
		glCompileShader(shader);

		// check
		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			char* errorLog = (char*)alloca(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);

			LT_ENGINE_ASSERT(false, "glShader::glShader: failed to compile vertex shader:\n        {}", errorLog);

			return NULL;
		}

#ifdef LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
		// info log
		{
			int logLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
			if (logLength)
			{
				char* infoLog = (char*)alloca(logLength);
				glGetShaderInfoLog(vertexShader, logLength, &logLength, &infoLog[0]);

				LT_ENGINE_TRACE(infoLog);
			}
		}
#endif

		return shader;
	}

}