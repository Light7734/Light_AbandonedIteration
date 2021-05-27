#include "ltpch.h"
#include "UserInterface.h"

#include "Graphics/GraphicsContext.h"

#include "OpenGL/glUserInterface.h"

namespace Light {

	UserInterface* UserInterface::Create(GLFWwindow* windowHandle)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glUserInterface(windowHandle);
		}
	}

}