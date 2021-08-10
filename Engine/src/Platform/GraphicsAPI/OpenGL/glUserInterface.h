#pragma once

#include "UserInterface/UserInterface.h"

#include "Base/Base.h"

struct GLFWwindow;

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

	private:
		void SetDarkThemeColors();
	};

}