#include "ltpch.h"
#include "Application.h"

#include "Logger.h"
#include "Window.h"

#include "Events/Event.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"

#include "UserInterface/UserInterface.h"

namespace Light {

	Application::Application()
	{
		Logger::Initialize();
		m_Window = std::unique_ptr<Light::Window>(Light::Window::Create(std::bind(&Light::Application::OnEvent, this, std::placeholders::_1)));
	}

	Application::~Application()
	{
		LT_ENGINE_TRACE("Application::~Application()");
	}

	void Application::GameLoop()
	{
		// check
		LT_ENGINE_ASSERT(!m_LayerStack.IsEmpty(), "Application::GameLoop: Layerstack is empty");

		// Log window data
		LogDebugData();
		m_Window->GetGfxContext()->LogDebugData();
		m_Window->GetGfxContext()->GetUserInterface()->LogDebugData();

		// Show window
		m_Window->SetVisible(true);

		//  GAMELOOP  //
		while (m_Window->IsOpen())
		{
			// Events
			m_Window->PollEvents();

			// Rendering
			m_Window->GetGfxContext()->GetRenderer()->BeginScene();
			m_LayerStack.OnRender();
			m_Window->GetGfxContext()->GetRenderer()->EndScene();

			// Buffer updates
			m_Window->GetGfxContext()->GetRenderCommand()->SwapBuffers();
			m_Window->GetGfxContext()->GetRenderCommand()->ClearBackBuffer();

			// Update
			// ...

			// UserInterface
			m_Window->GetGfxContext()->GetUserInterface()->Begin();
			m_Window->GetGfxContext()->GetUserInterface()->End();
		}
	}

	void Application::OnEvent(const Event& event)
	{
		// Window
		if (event.HasCategory(WindowEventCategory))
			m_Window->OnEvent(event);

		// UserInterface
		if (event.HasCategory(InputEventCategory))
			m_Window->GetGfxContext()->GetUserInterface()->OnInput(event);

		// Input
		// ...

		// Layers
		m_LayerStack.OnEvent(event);
	}

	void Application::LogDebugData()
	{
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("Platform::");
		LT_ENGINE_INFO("        OS: {}", LT_BUILD_PLATFORM);
		LT_ENGINE_INFO("________________________________________");
	}

}