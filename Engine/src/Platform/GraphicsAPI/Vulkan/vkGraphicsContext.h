#pragma once

#include "Graphics/GraphicsContext.h"

#include "Base/Base.h"

#include <vulkan/vulkan.h>

namespace Light {

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance m_VulkanInstance;

	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;
	};

}