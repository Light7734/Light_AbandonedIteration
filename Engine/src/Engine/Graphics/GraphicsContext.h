#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class Renderer;
	class RenderCommand;
	class UserInterface;

	enum class GraphicsAPI
	{
		Default = 0,
		OpenGL, 
		DirectX, 
		Vulkan, 
		Metal
	};

	class GraphicsContext
	{
	private:
		static GraphicsContext* s_Context;

		std::unique_ptr<Renderer> m_Renderer;
		std::shared_ptr<RenderCommand> m_RenderCommand;
		std::unique_ptr<UserInterface> m_UserInterface;

	protected:
		GraphicsAPI m_GraphicsAPI;

	public:
		GraphicsContext(const GraphicsContext&) = delete;
		GraphicsContext& operator=(const GraphicsContext&) = delete;

		virtual ~GraphicsContext() = default;
	
		static GraphicsContext* Create(GraphicsAPI api, GLFWwindow* windowHandle);

		static inline GraphicsAPI GetGraphicsAPI() { return s_Context->m_GraphicsAPI; }

		inline Renderer* GetRenderer() { return m_Renderer.get(); }
		inline RenderCommand* GetRenderCommand() { return m_RenderCommand.get(); }
		inline UserInterface* GetUserInterface() { return m_UserInterface.get(); }

	protected:
		GraphicsContext() = default;
	};

}