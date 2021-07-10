#include "ltpch.h"
#include "Application.h"

#include "Window.h"

#include "Events/Event.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"

#include "UserInterface/UserInterface.h"

#include "Time/Timer.h"

#include <filesystem>

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

		DeltaTimer deltaTimer;

		//** GAMELOOP **//
		while (!m_Window->IsClosed())
		{
			// update layers
			m_LayerStack.OnUpdate(deltaTimer.GetDeltaTime());

			// render layers
			m_Window->GetGfxContext()->GetRenderer()->BeginFrame();
			m_LayerStack.OnRender();
			m_Window->GetGfxContext()->GetRenderer()->EndFrame();

			// render user interface
			m_Window->GetGfxContext()->GetUserInterface()->Begin();
			m_Window->GetGfxContext()->GetUserInterface()->End();

			// poll events
			m_Window->PollEvents();

			/// update delta time
			deltaTimer.Update();
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
		LT_ENGINE_INFO("       DIR: {}", std::filesystem::current_path().generic_string());
		LT_ENGINE_INFO("________________________________________");
	}

}