#include "ltpch.h"
#include "Blender.h"
#include "OpenGL/glBlender.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBlender.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"


namespace Light {

	Blender* Blender::Create(std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glBlender();

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxBlender(std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "Blender::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
		}
	}

}