#pragma once

#include "Base.h"

struct GLFWwindow;

namespace Light {

	class UserInterface
	{
	private:
	public:
		static UserInterface* Create(GLFWwindow* windowHandle);

		virtual void Begin() = 0;
		virtual void End() = 0;
	};

}