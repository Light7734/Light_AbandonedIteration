#pragma once

#include "Base.h"

#include <memory>

namespace Light {

	class Window;

	class Application
	{
	private:
		std::unique_ptr<Window> m_Window = nullptr;

	public:
		virtual ~Application();

		void GameLoop();

		// To be defined in client project
		friend Application* CreateApplication();

	protected:
		Application();
	};

}