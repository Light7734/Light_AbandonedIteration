#include "GraphicsContext.hpp"

#include "OpenGL/glGraphicsContext.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxGraphicsContext.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "Blender.hpp"                     // required for forward declaration
#include "Buffers.hpp"                     // required for forward declaration
#include "RenderCommand.hpp"               // required for forward declaration
#include "Renderer.hpp"                    // required for forward declaration
#include "UserInterface/UserInterface.hpp" // required for forward declaration
#include "Utility/ResourceManager.hpp"     // required for forward declaration

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
		scopeGfx  = CreateScope<glGraphicsContext>(windowHandle);
		s_Context = scopeGfx.get();
		break;
	// directx
	case GraphicsAPI::DirectX: LT_WIN(
		scopeGfx  = CreateScope<dxGraphicsContext>(windowHandle);
		s_Context = scopeGfx.get();
		break;)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", Stringifier::GraphicsAPIToString(api));
		return nullptr;
	}

	// create 'GraphicsContext' dependent classes
	s_Context->m_UserInterface = UserInterface::Create(windowHandle, s_Context->m_SharedContext);
	s_Context->m_Renderer      = Renderer::Create(windowHandle, s_Context->m_SharedContext);

	// check
	ASSERT(s_Context->m_UserInterface, "Failed to create UserInterface");
	ASSERT(s_Context->m_Renderer, "Failed to create Renderer");

	return std::move(scopeGfx);
}

} // namespace Light
