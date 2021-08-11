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
		glUserInterface() = default;
		~glUserInterface();

		void PlatformImplementation(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext) override;

		void Begin() override;
		void End() override;

		void LogDebugData() override;
	};

}