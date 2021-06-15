#include "ltpch.h"
#include "Shader.h"
#include "OpenGL/glShader.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxShader.h"
#endif

#include "GraphicsContext.h"

#include "Utility/FileManager.h"

namespace Light {

	Shader* Shader::Create(const std::string& vertexPath, const std::string& pixelPath, void* sharedContext)
	{
		// load shader source
		std::string vertexSource = FileManager::ReadTXTFile(vertexPath);
		std::string pixelSource = FileManager::ReadTXTFile(pixelPath);

		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			ExtractShaderSource(vertexSource, "GLSL");
			ExtractShaderSource(pixelSource, "GLSL");

			return new glShader(vertexSource, pixelSource);

		case GraphicsAPI::DirectX: LT_WIN(
			ExtractShaderSource(vertexSource, "HLSL");
			ExtractShaderSource(pixelSource, "HLSL");

			return new dxShader(vertexSource, pixelSource, sharedContext);)

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	void Shader::ExtractShaderSource(std::string& src, const std::string& delim)
	{
		size_t begDelimPos, endDelimPos;

		begDelimPos = src.find('+' + delim) + 5;
		endDelimPos = src.find('-' + delim);

		LT_ENGINE_ASSERT(begDelimPos != std::string::npos + 5,
		                 "Shader::ExtractShaderSource: failed to find the start delimeter in shader source, delim: {}, shader:\n{}",
		                 delim, src);


		LT_ENGINE_ASSERT(endDelimPos != std::string::npos,
			"Shader::ExtractShaderSource: failed to find the end delimeter in shader source, delim: {}, shader:\n{}",
			delim, src);

		src = src.substr(begDelimPos, endDelimPos - begDelimPos);
	}

}