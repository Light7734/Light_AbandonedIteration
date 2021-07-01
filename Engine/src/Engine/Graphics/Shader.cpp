#include "ltpch.h"
#include "Shader.h"
#include "OpenGL/glShader.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxShader.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& pixelSource, std::shared_ptr<SharedContext> sharedContext)
	{
		// load shader source
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glShader(vertexSource, pixelSource);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxShader(vertexSource, pixelSource, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}