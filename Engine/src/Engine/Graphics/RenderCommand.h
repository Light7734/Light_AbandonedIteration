#pragma once

struct GLFWwindow;

namespace Light {

	class RenderCommand
	{
	private:
	public:
		static RenderCommand* Create(GLFWwindow* windowHandle);

		virtual void SwapBuffers() = 0;
		virtual void ClearBackBuffer() = 0;

		virtual void Draw(unsigned int count) = 0;
		virtual void DrawIndexed(unsigned int count) = 0;
	};

}