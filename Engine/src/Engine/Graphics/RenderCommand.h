#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class SharedContext;

	class RenderCommand
	{
	public:
		static RenderCommand* Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);

		RenderCommand(const RenderCommand&) = delete;
		RenderCommand& operator=(const RenderCommand&) = delete;

		virtual ~RenderCommand() = default;

		virtual void SwapBuffers() = 0;
		virtual void ClearBackBuffer() = 0;

		virtual void Draw(unsigned int count) = 0;
		virtual void DrawIndexed(unsigned int count) = 0;

	protected:
		RenderCommand() = default;
	};

}