#pragma once

#include "Base/Base.h"

#include "Debug/Instrumentor.h"

#include "Input/Input.h"

#include "Layer/LayerStack.h"

#include "Utility/ResourceManager.h"

namespace Light {

	class Window;
	class Event;

	class Instrumentor;

	class Application
	{
	private:
		static Application* s_Context;

	private:
		Scope<Logger> m_Logger;
		Scope<Instrumentor> m_Instrumentor;
		Scope<LayerStack> m_LayerStack;
		Scope<Input> m_Input;
		Scope<ResourceManager> m_ResourceManager;

	protected:
		Scope<Window> m_Window;

	public:
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void GameLoop();

		// To be defined in client project

		static void Quit();

	protected:
		Application();

	private:
		void OnEvent(const Event& event);

		void LogDebugData();
	};

	Application* CreateApplication();

}