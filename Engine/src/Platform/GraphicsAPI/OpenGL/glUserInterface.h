#pragma once

#include "Base.h"
#include "UserInterface/UserInterface.h"

class GLFWwindow;

namespace Light {

	class glUserInterface : public UserInterface
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		glUserInterface(GLFWwindow* windowHandle);
		~glUserInterface();

		void Begin() override;
		void End() override;

		void LogDebugData() override;
	};

}