#include "ltpch.h"
#include "Application.h"

#include "Window.h"

#include "Debug/Instrumentor.h"

#include "Events/Event.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"

#include "Layer/Layer.h"

#include "Time/Timer.h"

#include "UserInterface/UserInterface.h"

namespace Light {

	Application::Application()
		: m_Instrumentor(nullptr),
		  m_LayerStack(nullptr),
		  m_Input(nullptr),
		  m_Window(nullptr)
	{
		m_Logger = Logger::Create();
		LogDebugData();

		m_Instrumentor = Instrumentor::Create();
		m_Instrumentor->BeginSession("Logs/ProfileResults_Startup.json");

		m_LayerStack = LayerStack::Create();
		m_Input = Input::Create();

		m_Window = Window::Create(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
		LT_ENGINE_TRACE("Application::~Application()");
		m_Instrumentor->EndSession(); // ProfileResults_Termination //
	}

	void Application::GameLoop()
	{
		// check
		LT_ENGINE_ASSERT(!m_LayerStack->IsEmpty(), "Application::GameLoop(pre): LayerStack is empty");

		// log debug data
		m_Logger->LogDebugData();
		m_Window->GetGfxContext()->LogDebugData();
		m_Window->GetGfxContext()->GetUserInterface()->LogDebugData();

		// reveal window
		m_Window->SetVisibility(true);

		m_Instrumentor->EndSession(); // ProfileResults_GameLoop //
		m_Instrumentor->BeginSession("Logs/ProfileResults_GameLoop.json");

		/* game loop */
		DeltaTimer deltaTimer;
		while (!m_Window->IsClosed())
		{
			{
				// update layers
				LT_PROFILE_SCOPE("GameLoop::Update");
				LT_PROFILE_SCOPE("GameLoop::Updated");

				for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
					(*it)->OnUpdate(deltaTimer.GetDeltaTime());
			}

			{
				// render layers
				LT_PROFILE_SCOPE("GameLoop::Render");
				m_Window->GetGfxContext()->GetRenderer()->BeginFrame();

				for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
					(*it)->OnRender();

				m_Window->GetGfxContext()->GetRenderer()->EndFrame();
			}

			{
				// render user interface
				LT_PROFILE_SCOPE("GameLoop::UserInterface");
				m_Window->GetGfxContext()->GetUserInterface()->Begin();

				for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
					(*it)->OnUserInterfaceUpdate();

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
		{
			m_Window->OnEvent(event);

			if(event.GetEventType() == EventType::WindowResized)
				m_Window->GetGfxContext()->GetRenderer()->OnWindowResize((const WindowResizedEvent&)event);
		}

		// input
		if (event.HasCategory(InputEventCategory))
		{
			m_Input->OnEvent(event);

			if(!m_Input->IsReceivingGameEvents()) // return if the event is an input event and 'Input' has disabled the game events
				return;
		}

		/* layers */
		for (auto it = m_LayerStack->rbegin(); it != m_LayerStack->rend(); it++)
			if ((*it)->OnEvent(event)) return;
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