#include "Application.h"

#include "Logger.h"

namespace Light {

	Application::Application()
	{
		Logger::Initialize();

		LT_ENGINE_INFO("Initialized Logger");
	}

	Application::~Application()
	{
	}

	void Application::GameLoop()
	{
		while (true);
	}

}