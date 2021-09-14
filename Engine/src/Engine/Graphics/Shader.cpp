#include "ltpch.h"
#include "Shader.h"
#include "OpenGL/glShader.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxShader.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	Ref<Shader> Shader::Create(const std::vector<uint8_t>& vertexBlob, const std::vector<uint8_t>& pixelBlob, const std::string& vertexFileName, const std::string& pixelFileName, Ref<SharedContext> sharedContext)
	{
		// load shader source
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateRef<glShader>(vertexBlob, pixelBlob, vertexFileName, pixelFileName);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateRef<dxShader>(vertexBlob, pixelBlob, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}