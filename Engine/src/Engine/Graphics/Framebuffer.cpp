#include "Framebuffer.h"

#include "OpenGL/glFramebuffer.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxFramebuffer.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glFramebuffer>(specification);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxFramebuffer>(specification, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
		return nullptr;
	}
}

} // namespace Light
