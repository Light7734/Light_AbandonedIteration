#include "ltpch.h"
#include "GraphicsContext.h"
#include "OpenGL/glGraphicsContext.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxGraphicsContext.h"
#endif

#include "Buffers.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "UserInterface/UserInterface.h" 

#include "Utility/ResourceManager.h"
#include "Utility/Stringifier.h"

namespace Light {

	GraphicsContext* GraphicsContext::s_Context = nullptr;

	GraphicsContext::~GraphicsContext() { }

	GraphicsContext* GraphicsContext::Create(GraphicsAPI api, GLFWwindow* windowHandle)
	{
		// terminate gfx context dependent classes
		if (s_Context)
		{
			s_Context->m_Renderer.reset();
			s_Context->m_RenderCommand.reset();
			s_Context->m_UserInterface.reset();

			delete s_Context;
		}

		// determine the default api
		if (api == GraphicsAPI::Default)
		{
#if defined(LIGHT_PLATFORM_WINDOWS)
			api = GraphicsAPI::DirectX;
#elif defined(LIGHT_PLATFORM_LINUX)
			// #todo:
#elif defined(LIGHT_PLATFORM_MAC)
			// #todo:
#endif
		}

		// create gfx context
		switch (api)
		{
		case GraphicsAPI::OpenGL:
			s_Context = new glGraphicsContext(windowHandle);
			break;

		case GraphicsAPI::DirectX: LT_WIN(
			s_Context = new dxGraphicsContext(windowHandle);
			break;)

		default:
			LT_ENGINE_ASSERT(false, "GraphicsContext::Create: invalid/unsupported GraphicsAPI {}", Stringifier::GraphicsAPIToString(api));
			return nullptr;
		}

		// create gfx context dependent classes
		s_Context->m_ResourceManager = std::unique_ptr<ResourceManager>(ResourceManager::Create(s_Context->m_SharedContext));

		s_Context->m_RenderCommand = std::unique_ptr<RenderCommand>(RenderCommand::Create(windowHandle, s_Context->m_SharedContext));
		s_Context->m_UserInterface = std::unique_ptr<UserInterface>(UserInterface::Create(windowHandle, s_Context->m_SharedContext));
		s_Context->m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(s_Context->m_RenderCommand, s_Context->m_SharedContext));

		// sanity check
		LT_ENGINE_ASSERT(s_Context->m_RenderCommand, "GraphicsContext::Create: failed to create RenderCommand");
		LT_ENGINE_ASSERT(s_Context->m_UserInterface, "GraphicsContext::Create: failed to create UserInterface");
		LT_ENGINE_ASSERT(s_Context->m_Renderer, "GraphicsContext::Create: failed to create Renderer");

		return s_Context;
	}

}