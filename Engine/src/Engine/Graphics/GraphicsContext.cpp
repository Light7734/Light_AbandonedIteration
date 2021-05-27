#include "ltpch.h"
#include "GraphicsContext.h"
#include "OpenGL/glGraphicsContext.h"

#include "RenderCommand.h"
#include "UserInterface/UserInterface.h" 

namespace Light {

	GraphicsContext* GraphicsContext::s_Context = nullptr;

	GraphicsContext* GraphicsContext::Create(GraphicsAPI api, GLFWwindow* windowHandle)
	{
		// terminate gfx context dependent classes
		if (s_Context)
		{
			s_Context->m_RenderCommand.reset();
			s_Context->m_UserInterface.reset();
		}

		// create gfx context
		switch (api)
		{
		case Light::GraphicsAPI::Default:
		case Light::GraphicsAPI::OpenGL:
			s_Context = new glGraphicsContext(windowHandle);
			break;
		default:
			break;
			// TODO: ASSERT
		}

		// create gfx context dependent classes
		if (s_Context)
		{
			s_Context->m_RenderCommand = std::unique_ptr<RenderCommand>(RenderCommand::Create(windowHandle));
			s_Context->m_UserInterface = std::unique_ptr<UserInterface>(UserInterface::Create(windowHandle));
			// ...Renderer
			// ...UserInterface...
		}

		return s_Context;
	}

}