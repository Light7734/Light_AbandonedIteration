#pragma once

#include "Base.h"

#include "Debug/Instrumentor.h"

#include "Layer/LayerStack.h"

#include "Input/Input.h"

namespace Light {

	class Window;
	class Event;

	class Instrumentor;

	class Application
	{
	private:
		std::unique_ptr<Instrumentor> m_Instrumentor = nullptr;
		LayerStack m_LayerStack;
		Input m_Input;

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