#include "ltpch.h"
#include "Application.h"

#include "Logger.h"
#include "Window.h"

#include "Events/MouseEvents.h"

#include <typeinfo>
#include <functional>

namespace Light {

	Application::Application()
	{
		Logger::Initialize();

		m_Window = std::unique_ptr<Window>(Window::Create({ "Title", 800u, 600u, false }, std::bind(&Application::OnEvent, this , std::placeholders::_1)));

		LT_ENGINE_INFO("Initialized Logger");
	}

	Application::~Application()
	{
	}

	void Application::GameLoop()
	{
		while (m_Window->IsOpen())
		{
			m_Window->PollEvents();

			m_Window->GetGfxContext()->GetRenderCommand()->SwapBuffers();
			m_Window->GetGfxContext()->GetRenderCommand()->ClearBackBuffer();

			m_Window->GetGfxContext()->GetUserInterface()->Begin();

			m_Window->GetGfxContext()->GetUserInterface()->End();
		}
	}

	void Application::OnEvent(const Event& event)
	{
		if (event.HasCategory(WindowEventCategory))
			m_Window->OnEvent(event);

		if (event.HasCategory(InputEventCategory))
			m_Window->GetGfxContext()->GetUserInterface()->OnInput(event);

		m_LayerStack.OnEvent(event);
	}

}