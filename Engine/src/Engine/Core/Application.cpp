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

		TestLayer* layer = new TestLayer("Test Layer");
		m_LayerStack.PushLayer(layer);

		LT_ENGINE_INFO("Initialized Logger");
	}

	Application::~Application()
	{
	}

	void Application::GameLoop()
	{
		while (true) { m_Window->OnUpdate(); }
	}

	void Application::OnEvent(Event& event)
	{
		m_Dispatcher.Dispatch(event, m_LayerStack.begin(), m_LayerStack.end());
	}

}