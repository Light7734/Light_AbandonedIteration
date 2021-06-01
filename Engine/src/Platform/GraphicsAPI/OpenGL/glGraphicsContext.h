#pragma once

#include "Base.h"
#include "Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Light {

	class WindowResizedEvent;

	class glGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		glGraphicsContext(GLFWwindow* windowHandle);

		virtual void OnWindowResize(const WindowResizedEvent& event) override;

		virtual void LogDebugData() override;

	private:
		void SetDebugMessageCallback();
	};

}