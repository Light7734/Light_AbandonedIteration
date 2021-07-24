#include "ltpch.h"
#include "glRenderCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	glRenderCommand::glRenderCommand(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{ }

	void glRenderCommand::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void glRenderCommand::ClearBackBuffer(const glm::vec4& clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void glRenderCommand::Draw(unsigned int count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void glRenderCommand::DrawIndexed(unsigned int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void glRenderCommand::DefaultTargetFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	}

	void glRenderCommand::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

}