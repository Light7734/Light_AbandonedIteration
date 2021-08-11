#pragma once

#include "Base/Base.h"

struct GLFWwindow;

namespace Light {

	class Event;

	class SharedContext;

	// #todo: fix the UserIntreface mess!!
	class UserInterface
	{
	public:
		static Scope<UserInterface> Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext);

		UserInterface(const UserInterface&) = delete;
		UserInterface& operator=(const UserInterface&) = delete;

		virtual ~UserInterface() = default;

		void Init(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext);

		virtual void PlatformImplementation(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext) = 0;

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void LogDebugData() = 0;

	protected:
		UserInterface() = default;

	private:
		void SetDarkThemeColors();
	};

}