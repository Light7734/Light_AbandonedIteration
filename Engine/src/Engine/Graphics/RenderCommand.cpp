#include "ltpch.h"
#include "RenderCommand.h"
#include "OpenGL/glRenderCommand.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxRenderCommand.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	RenderCommand* RenderCommand::Create(GLFWwindow* windowHandle, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glRenderCommand(windowHandle);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxRenderCommand(sharedContext);)

		default:
			LT_ENGINE_ASSERT(false, "RenderCommand::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}