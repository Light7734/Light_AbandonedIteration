#pragma once

#include "Base/Base.hpp"
#include "Graphics/RenderCommand.hpp"

struct GLFWwindow;

namespace Light {

class glRenderCommand: public RenderCommand
{
private:
	GLFWwindow* m_WindowHandle;

public:
	glRenderCommand(GLFWwindow* windowHandle);

	void SwapBuffers() override;
	void ClearBackBuffer(const glm::vec4& clearColor) override;

	void Draw(unsigned int count) override;
	void DrawIndexed(unsigned int count) override;

	void DefaultTargetFramebuffer() override;

	void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
};

} // namespace Light