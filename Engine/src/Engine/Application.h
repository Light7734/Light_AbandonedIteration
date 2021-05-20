#pragma once

#include "Base.h"

namespace Light {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void GameLoop();
	};

	Application* CreateApplication();

}