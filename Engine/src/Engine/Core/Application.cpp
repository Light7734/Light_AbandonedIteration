#include "ltpch.h"
#include "Application.h"

#include "Window.h"

#include "Events/Event.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"

#include "UserInterface/UserInterface.h"

#include "Debug/Instrumentor.h"

#include "Time/Timer.h"

#include <filesystem>

namespace Light {

	Application::Application()
	{
		Logger::Initialize();
		m_Instrumentor = std::unique_ptr<Instrumentor>(Instrumentor::Create());

		m_Instrumentor->BeginSession("Logs/ProfileResults_Startup.json");
		m_Window = std::unique_ptr<Light::Window>(Light::Window::Create(std::bind(&Light::Application::OnEvent, this, std::placeholders::_1)));
	}

	Application::~Application()
	{
		LT_ENGINE_TRACE("Application::~Application()");
		m_Instrumentor->EndSession(); // ProfileResults_Termination //
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

		m_Instrumentor->EndSession(); // ProfileResults_GameLoop //
		m_Instrumentor->BeginSession("Logs/ProfileResults_GameLoop.json");

		//** GAMELOOP **//
		DeltaTimer deltaTimer;
		while (!m_Window->IsClosed())
		{
			{
				// update layers
				LT_PROFILE_SCOPE("GameLoop::Update");
				m_LayerStack.OnUpdate(deltaTimer.GetDeltaTime());
			}

			{
				// render layers
				LT_PROFILE_SCOPE("GameLoop::Render");
				m_Window->GetGfxContext()->GetRenderer()->BeginFrame();
				m_LayerStack.OnRender();
				m_Window->GetGfxContext()->GetRenderer()->EndFrame();
			}

			{
				// render user interface
				LT_PROFILE_SCOPE("GameLoop::UserInterface");
				m_Window->GetGfxContext()->GetUserInterface()->Begin();
				m_Window->GetGfxContext()->GetUserInterface()->End();
			}

			{
				// poll events
				LT_PROFILE_SCOPE("GameLoop::Events");
				m_Window->PollEvents();
			}

			/// update delta time
			deltaTimer.Update();
		}
		
		m_Instrumentor->EndSession(); // ProfileResults_GameLoop //
		m_Instrumentor->BeginSession("Logs/ProfileResults_Termination.json");
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