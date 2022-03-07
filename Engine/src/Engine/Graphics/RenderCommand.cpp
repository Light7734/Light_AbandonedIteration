#include "RenderCommand.h"

#include "OpenGL/glRenderCommand.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxRenderCommand.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

Scope<RenderCommand> RenderCommand::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateScope<glRenderCommand>(windowHandle);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateScope<dxRenderCommand>((std::static_pointer_cast<dxSharedContext>)(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
		return nullptr;
	}
}

} // namespace Light
