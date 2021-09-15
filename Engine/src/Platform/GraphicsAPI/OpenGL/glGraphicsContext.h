#pragma once

#include "Graphics/GraphicsContext.h"

#include "Base/Base.h"

struct GLFWwindow;

namespace Light {

	class glGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		glGraphicsContext(GLFWwindow* windowHandle);

		void LogDebugData() override;

	private:
		void SetupDebugMessageCallback();
	};

}