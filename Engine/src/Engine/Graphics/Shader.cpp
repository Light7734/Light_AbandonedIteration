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
		const std::string vertexSource = FileManager::ReadTXTFile(vertexPath);
		const std::string pixelSource = FileManager::ReadTXTFile(pixelPath);

		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glShader(vertexSource, pixelSource);

		case GraphicsAPI::DirectX:
			return new dxShader(vertexSource, pixelSource, sharedContext);

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}