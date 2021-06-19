#include "ltpch.h"
#include "RenderCommand.h"
#include "OpenGL/glRenderCommand.h"

#include "SharedContext.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxRenderCommand.h"
	#include "Directx/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	RenderCommand* RenderCommand::Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glRenderCommand(windowHandle);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxRenderCommand((std::static_pointer_cast<dxSharedContext>)(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "RenderCommand::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}