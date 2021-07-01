#include "ltpch.h"
#include "GraphicsContext.h"
#include "OpenGL/glGraphicsContext.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxGraphicsContext.h"
	#include "DirectX/dxSharedContext.h"
#endif

// forward declaration
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "UserInterface/UserInterface.h"
#include "Utility/ResourceManager.h"

namespace Light {

	GraphicsContext* GraphicsContext::s_Context = nullptr;

	GraphicsContext::~GraphicsContext() { }

	GraphicsContext* GraphicsContext::Create(GraphicsAPI api, GLFWwindow* windowHandle)
	{
		// terminate 'GraphicsContext' dependent classes
		if (s_Context)
		{
			s_Context->m_Renderer.reset();
			s_Context->m_UserInterface.reset();

			delete s_Context;
		}
		
		// determine the default api
		if (api == GraphicsAPI::Default)
		{
#if defined(LIGHT_PLATFORM_WINDOWS)
			api = GraphicsAPI::DirectX;
#elif defined(LIGHT_PLATFORM_LINUX)
			api = GraphicsContext::OpenGL;
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
			LT_ENGINE_ASSERT(false, "GraphicsContext::Create: invalid/unsupported 'GraphicsAPI' {}", Stringifier::GraphicsAPIToString(api));
			return nullptr;
		}

		// create 'GraphicsContext' dependent classes
		s_Context->m_ResourceManager = std::unique_ptr<ResourceManager>(ResourceManager::Create(s_Context->m_SharedContext));
		s_Context->m_UserInterface = std::unique_ptr<UserInterface>(UserInterface::Create(windowHandle, s_Context->m_SharedContext));
		s_Context->m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(windowHandle, s_Context->m_SharedContext));

		// check
		LT_ENGINE_ASSERT(s_Context->m_ResourceManager, "GraphicsContext::Create: failed to create ResourceManager");
		LT_ENGINE_ASSERT(s_Context->m_UserInterface, "GraphicsContext::Create: failed to create UserInterface");
		LT_ENGINE_ASSERT(s_Context->m_Renderer, "GraphicsContext::Create: failed to create Renderer");

		return s_Context;
	}

}