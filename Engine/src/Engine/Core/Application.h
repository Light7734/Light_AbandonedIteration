#pragma once

#include "Base/Base.h"

#include "Debug/Instrumentor.h"

#include "Input/Input.h"

#include "Layer/LayerStack.h"

namespace Light {

	class Window;
	class Event;

	class Instrumentor;

	class Application
	{
	private:
		Scope<Logger> m_Logger;
		Scope<Instrumentor> m_Instrumentor;
		Scope<LayerStack> m_LayerStack;
		Scope<Input> m_Input;

	protected:
		Scope<Window> m_Window;

	public:
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void GameLoop();

	protected:
		Application();

	private:
		void OnEvent(const Event& event);

		void LogDebugData();
	};

	Application* CreateApplication(); // can't define it inside the class as friend with c++20?

}