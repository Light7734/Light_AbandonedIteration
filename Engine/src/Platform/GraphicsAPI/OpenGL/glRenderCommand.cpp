#include "ltpch.h"
#include "glRenderCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	glRenderCommand::glRenderCommand(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void glRenderCommand::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void glRenderCommand::ClearBackBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.25f, 0.45f, 0.91f, 1.0f);
	}

	void glRenderCommand::Draw(unsigned int count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void glRenderCommand::DrawIndexed(unsigned int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

}