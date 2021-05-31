#include "ltpch.h"
#include "Shader.h"
#include "OpenGL/glShader.h"

#include "GraphicsContext.h"

#include "Utility/FileManager.h"

namespace Light {

	Shader* Shader::Create(const std::string& vertexPath, const std::string& pixelPath)
	{
		// load shader source
		const std::string vertexSource = FileManager::ReadTXTFile(vertexPath);
		const std::string pixelSource = FileManager::ReadTXTFile(pixelPath);

		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glShader(vertexSource, pixelSource);

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}