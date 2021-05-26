#pragma once

#include "Base.h"
#include "Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Light {

	class glGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		glGraphicsContext(GLFWwindow* windowHandle);
	};

}