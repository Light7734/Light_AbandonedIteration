#include "ltpch.h"
#include "Application.h"

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
		LT_ENGINE_ASSERT(!m_LayerStack.IsEmpty(), "Application::GameLoop(pre): LayerStack is empty");

		// log debug data
		LogDebugData();
		Logger::LogDebugData();
		m_Window->GetGfxContext()->LogDebugData();
		m_Window->GetGfxContext()->GetUserInterface()->LogDebugData();

		// reveal window
		m_Window->SetVisibility(true);

		//*  [ GAMELOOP ] *//
		while (!m_Window->IsClosed())
		{
			// update layyers
			m_LayerStack.OnUpdate(1000.0f / 60.0f); // #todo: implement time

			// render layers
			m_Window->GetGfxContext()->GetRenderer()->BeginScene();
			m_LayerStack.OnRender();
			m_Window->GetGfxContext()->GetRenderer()->EndScene();

			// render user interface
			m_Window->GetGfxContext()->GetUserInterface()->Begin();
			m_Window->GetGfxContext()->GetUserInterface()->End();

			// swap buffers
			m_Window->GetGfxContext()->GetRenderCommand()->SwapBuffers();
			m_Window->GetGfxContext()->GetRenderCommand()->ClearBackBuffer();

			// poll events
			m_Window->PollEvents();
		}
	}

	void Application::OnEvent(const Event& event)
	{
		// window
		if (event.HasCategory(WindowEventCategory))
			m_Window->OnEvent(event);

		// user interface
		if (event.HasCategory(InputEventCategory))
			m_Window->GetGfxContext()->GetUserInterface()->OnInput(event);

		// #todo: add input manager
		// ...

		// layers
		m_LayerStack.OnEvent(event);
	}

	void Application::LogDebugData()
	{
		// #todo: log more information
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("Platform::");
		LT_ENGINE_INFO("        OS: {}", LT_BUILD_PLATFORM);
		LT_ENGINE_INFO("________________________________________");
	}

}