#pragma once

#include "Base.h"
#include "UserInterface/UserInterface.h"

namespace Light {

	class glUserInterface : public UserInterface
	{
	public:
		glUserInterface(GLFWwindow* windowHandle);
		~glUserInterface();

		void Begin() override;
		void End() override;

		virtual void LogDebugData() override;
	};

}