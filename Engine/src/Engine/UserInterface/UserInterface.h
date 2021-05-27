#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class Event;

	class UserInterface
	{
	public:
		UserInterface(const UserInterface&) = delete;
		UserInterface operator=(const UserInterface&) = delete;

		virtual ~UserInterface() = default;

		void OnInput(const Event& inputEvent);

		virtual void Begin() = 0;
		virtual void End() = 0;

		static UserInterface* Create(GLFWwindow* windowHandle);
	protected:
		UserInterface() = default;
	};

}