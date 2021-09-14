#pragma once

#include "Base/Base.h"

struct GLFWwindow;

namespace Light {

	class vkGraphicsContext
	{
	private:
	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();
	};

}