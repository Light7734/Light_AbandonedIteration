#pragma once

#include "Base.h"

#include "Layer/LayerStack.h"

namespace Light {

	class Window;
	class Event;

	class Application
	{
	private:
		LayerStack m_LayerStack;

	protected:
		std::unique_ptr<Window> m_Window = nullptr;

	public:
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void GameLoop();

		// To be defined in client project
		friend Application* CreateApplication();

	protected:
		Application();

	private:
		void OnEvent(const Event& event);

		void LogDebugData();
	};

}