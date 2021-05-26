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
		glClearColor(0.32f, 0.65f, 0.892f, 1.0f);
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