#include "ltpch.h"
#include "Framebuffer.h"
#include "OpenGL/glFramebuffer.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxFramebuffer.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& specification, std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glFramebuffer(specification);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxFramebuffer(specification, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "Shader::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}