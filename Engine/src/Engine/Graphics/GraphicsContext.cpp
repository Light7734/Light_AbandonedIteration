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

		// determine the default api
		if (api == GraphicsAPI::Default)
		{
#ifdef LIGHT_PLATFORM_WINDOWS
			api = GraphicsAPI::OpenGL; // TODO: Change to DirectX
#endif
		}

		// create gfx context
		switch (api)
		{
		case Light::GraphicsAPI::OpenGL:
			s_Context = new glGraphicsContext(windowHandle);
			break;

		default:
			LT_ENGINE_ASSERT(false, "GraphicsContext::Create: invalid/unsupported GraphicsAPI {}", api);
			return nullptr;
		}

		// create gfx context dependent classes
		s_Context->m_RenderCommand = std::unique_ptr<RenderCommand>(RenderCommand::Create(windowHandle));
		s_Context->m_UserInterface = std::unique_ptr<UserInterface>(UserInterface::Create(windowHandle));
		// ...Renderer
		// ...UserInterface...

		// sanity check
		LT_ENGINE_ASSERT(s_Context->m_RenderCommand, "GraphicsContext::Create: RenderCommand creation failed");
		LT_ENGINE_ASSERT(s_Context->m_UserInterface, "GraphicsContext::Create: UserInterface creation failed");


		return s_Context;
	}

}