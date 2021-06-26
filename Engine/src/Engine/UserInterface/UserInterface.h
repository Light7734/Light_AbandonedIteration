#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class Event;
	class SharedContext;

	class UserInterface
	{
	public:
		static UserInterface* Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);

		UserInterface(const UserInterface&) = delete;
		UserInterface& operator=(const UserInterface&) = delete;

		virtual ~UserInterface() = default;

		void OnInput(const Event& inputEvent);

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void LogDebugData() = 0;

	protected:
		UserInterface() = default;
	};

}