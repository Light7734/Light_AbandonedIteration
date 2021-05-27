#pragma once

#include "Base.h"
#include "Graphics/RenderCommand.h"

namespace Light {

	class glRenderCommand : public RenderCommand
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		glRenderCommand(GLFWwindow* windowHandle);

		void SwapBuffers() override;
		void ClearBackBuffer() override;

		void Draw(unsigned int count) override;
		void DrawIndexed(unsigned int count) override;
	};

}