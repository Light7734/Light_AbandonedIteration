#pragma once

#include "Base.h"

#include "RenderCommand.h"

#include "UserInterface/UserInterface.h"

struct GLFWwindow {};

namespace Light {

	enum class GraphicsAPI 
	{
		Default, OpenGL // TODO: Add DirectX, Vulkan, Metal.
	};

	class GraphicsContext
	{
	private:
		static GraphicsContext* s_Context;

		std::unique_ptr<RenderCommand> m_RenderCommand;
		std::unique_ptr<UserInterface> m_UserInterface;
	protected:
		GraphicsAPI m_GraphicsAPI;

	public:
		virtual ~GraphicsContext() = default;

		static GraphicsContext* Create(GraphicsAPI api, GLFWwindow* windowHandle);

		static inline GraphicsAPI GetGraphicsAPI() { return s_Context->m_GraphicsAPI; }

		inline RenderCommand* GetRenderCommand() { return m_RenderCommand.get(); }
		inline UserInterface* GetUserInterface() { return m_UserInterface.get(); }
	};

}