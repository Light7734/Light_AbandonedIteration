#include "ltpch.h"
#include "UserInterface.h"
#include "OpenGL/glUserInterface.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxUserInterface.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "Events/Event.h"
#include "Events/CharEvent.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

#include "Graphics/GraphicsContext.h"

#include <imgui.h>

namespace Light {

	Scope<UserInterface> UserInterface::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateScope<glUserInterface>(windowHandle);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateScope<dxUserInterface>(windowHandle, std::dynamic_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "UserInterface::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}