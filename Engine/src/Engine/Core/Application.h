#pragma once

#include "Base.h"

#include "Events/Event.h"
#include "Events/Dispatcher.h"

#include "Layer/LayerStack.h"

#include <memory>

namespace Light {

	class Window;

	class Application
	{
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		LayerStack m_LayerStack;
		Dispatcher m_Dispatcher;
	public:
		virtual ~Application();

		void GameLoop();
		void OnEvent(Event& event);

		// To be defined in client project
		friend Application* CreateApplication();

	protected:
		Application();
	};

}