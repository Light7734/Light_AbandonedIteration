#include "Blender.h"

#include "OpenGL/glBlender.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBlender.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

Scope<Blender> Blender::Create(Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateScope<glBlender>();

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateScope<dxBlender>(std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
	}
}

} // namespace Light
