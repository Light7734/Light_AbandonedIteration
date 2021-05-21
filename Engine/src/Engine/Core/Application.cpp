#include "Application.h"

#include "Logger.h"
#include "Window.h"

namespace Light {

	Application::Application()
	{
		Logger::Initialize();

		m_Window = std::unique_ptr<Window>(Window::Create({ "Title", 800u, 600u, false }));

		LT_ENGINE_INFO("Initialized Logger");
	}

	Application::~Application()
	{
	}

	void Application::GameLoop()
	{
		while (true) { m_Window->OnUpdate(); }
	}

}