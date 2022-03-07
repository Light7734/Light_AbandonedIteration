#include "Shader.h"

#include "OpenGL/glShader.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxShader.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

Ref<Shader> Shader::Create(BasicFileHandle vertexFile, BasicFileHandle pixelFile, Ref<SharedContext> sharedContext)
{
	// load shader source
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glShader>(vertexFile, pixelFile);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxShader>(vertexFile, pixelFile, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
		return nullptr;
	}
}

} // namespace Light
