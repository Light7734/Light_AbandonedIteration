#include "ltpch.h"
#include "GraphicsContext.h"

#include "OpenGL/glGraphicsContext.h"

namespace Light {

	GraphicsContext* GraphicsContext::s_Context = nullptr;

	GraphicsContext* GraphicsContext::Create(GraphicsAPI api, GLFWwindow* windowHandle)
	{
		switch (api)
		{
		case Light::GraphicsAPI::Default:
		case Light::GraphicsAPI::OpenGL:
			s_Context = new glGraphicsContext(windowHandle);
			s_Context->m_RenderCommand = std::unique_ptr<RenderCommand>(RenderCommand::Create(windowHandle));
			s_Context->m_UserInterface = std::unique_ptr<UserInterface>(UserInterface::Create(windowHandle));
			// ...Renderer
			// ...UserInterface...

			return s_Context;

		default:
			return nullptr; // TODO: Add ASSERT
		}
	}

}