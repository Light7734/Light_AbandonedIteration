#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class ResourceManager;
	class UserInterface;
	class Renderer;

	class SharedContext;

	class WindowResizedEvent;

	enum class GraphicsAPI
	{
		Default = 0,
		OpenGL, 
		DirectX, 
		Vulkan, // :#todo
		Metal   // :#todo
	};

	class GraphicsContext
	{
	private:
		static GraphicsContext* s_Context;

		std::unique_ptr<ResourceManager> m_ResourceManager;
		std::unique_ptr<UserInterface> m_UserInterface;
		std::unique_ptr<Renderer> m_Renderer;

	protected:
		GraphicsAPI m_GraphicsAPI;
		std::shared_ptr<SharedContext> m_SharedContext = nullptr;

	public:
		static GraphicsContext* Create(GraphicsAPI api, GLFWwindow* windowHandle);

		GraphicsContext(const GraphicsContext&) = delete;
		GraphicsContext& operator=(const GraphicsContext&) = delete;

		virtual ~GraphicsContext();

		virtual void OnWindowResize(const WindowResizedEvent& event) = 0;

		virtual void LogDebugData() = 0;

		static inline GraphicsAPI GetGraphicsAPI() { return s_Context->m_GraphicsAPI; }

		inline Renderer* GetRenderer() { return m_Renderer.get(); }
		inline UserInterface* GetUserInterface() { return m_UserInterface.get(); }

	protected:
		GraphicsContext() = default;

	};

}