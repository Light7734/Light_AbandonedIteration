#include "ltpch.h"
#include "RenderCommand.h"

#include "GraphicsContext.h"

#include "OpenGL/glRenderCommand.h"

namespace Light {

	RenderCommand* RenderCommand::Create(GLFWwindow* windowHandle)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glRenderCommand(windowHandle);

		default:
			return nullptr; // TODO: Add ASSERT
		}
	}

}