#include "ltpch.h"
#include "RenderCommand.h"
#include "OpenGL/glRenderCommand.h"

#include "GraphicsContext.h"

namespace Light {

	RenderCommand* RenderCommand::Create(GLFWwindow* windowHandle)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glRenderCommand(windowHandle);

		default:
			LT_ENGINE_ASSERT(false, "RenderCommand::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}