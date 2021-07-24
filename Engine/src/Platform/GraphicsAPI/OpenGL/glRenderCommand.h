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
		void ClearBackBuffer(const glm::vec4& clearColor) override;

		void Draw(unsigned int count) override;
		void DrawIndexed(unsigned int count) override;

		virtual void DefaultTargetFramebuffer() override;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
	};

}