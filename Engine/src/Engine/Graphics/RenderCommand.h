#pragma once

#include "Base.h"

#include <glm/glm.hpp>

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
		virtual void ClearBackBuffer(const glm::vec4& clearColor) = 0;

		virtual void Draw(unsigned int count) = 0;
		virtual void DrawIndexed(unsigned int count) = 0;

		virtual void DefaultTargetFramebuffer() = 0;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

	protected:
		RenderCommand() = default;
	};

}