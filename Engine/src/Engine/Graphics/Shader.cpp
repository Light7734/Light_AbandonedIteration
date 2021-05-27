#include "ltpch.h"
#include "Shader.h"
#include "OpenGL/glShader.h"

#include "GraphicsContext.h"

namespace Light {

	Shader* Shader::Create(const std::string& vertexPath, const std::string& pixelPath)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glShader(vertexPath, pixelPath);

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}