#include "ltpch.h"
#include "GraphicsContext.h"
#include "OpenGL/glGraphicsContext.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxGraphicsContext.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "Blender.h" // required for forward declaration
#include "Buffers.h" // required for forward declaration
#include "Renderer.h" // required for forward declaration
#include "RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

namespace Light {

	GraphicsContext* GraphicsContext::s_Context = nullptr;

	GraphicsContext::~GraphicsContext() 
	{
	}

	Scope<GraphicsContext> GraphicsContext::Create(GraphicsAPI api, GLFWwindow* windowHandle)
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
			api = GraphicsAPI::OpenGL;
#elif defined(LIGHT_PLATFORM_MAC)
			api = GraphicsAPI::OpenGL;
#endif
		}

		// create gfx context
		Scope<GraphicsContext> scopeGfx;
		switch (api)
		{
		// opengl
		case GraphicsAPI::OpenGL:
			scopeGfx = CreateScope<glGraphicsContext>(windowHandle);
			s_Context = scopeGfx.get();
			break;
		// directx
		case GraphicsAPI::DirectX: LT_WIN(
			scopeGfx = CreateScope<dxGraphicsContext>(windowHandle);
			s_Context = scopeGfx.get();
			break;)

		default:
			LT_ENGINE_ASSERT(false, "GraphicsContext::Create: invalid/unsupported 'GraphicsAPI' {}", Stringifier::GraphicsAPIToString(api));
			return nullptr;
		}

		// create 'GraphicsContext' dependent classes
		s_Context->m_UserInterface = UserInterface::Create(windowHandle, s_Context->m_SharedContext);
		s_Context->m_Renderer = Renderer::Create(windowHandle, s_Context->m_SharedContext);

		// check
		LT_ENGINE_ASSERT(s_Context->m_UserInterface, "GraphicsContext::Create: failed to create UserInterface");
		LT_ENGINE_ASSERT(s_Context->m_Renderer, "GraphicsContext::Create: failed to create Renderer");

		return std::move(scopeGfx);
	}

}