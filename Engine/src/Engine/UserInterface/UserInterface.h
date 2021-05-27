#pragma once

#include "Base.h"

#include "Events/Event.h"

struct GLFWwindow;

namespace Light {

	class UserInterface
	{
	private:
	public:
		static UserInterface* Create(GLFWwindow* windowHandle);

		void OnInput(const Event& inputEvent);

		virtual void Begin() = 0;
		virtual void End() = 0;
	};

}