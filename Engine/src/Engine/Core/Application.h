#pragma once

#include "Base.h"

#include "Layer/LayerStack.h"

namespace Light {

	class Window;
	class Event;

	class Application
	{
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		LayerStack m_LayerStack;

	public:
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void GameLoop();
		void OnEvent(const Event& event);

		// To be defined in client project
		friend Application* CreateApplication();

	protected:
		Application();
	};

}