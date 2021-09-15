#pragma once

#include "Graphics/GraphicsContext.h"
#include "Base/Base.h"

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Light {

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		VkInstance m_VkInstance;

		std::vector<const char*> m_ValidationLayers;
		std::vector<const char*> m_GlobalExtensions;

	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;


	private:
		void FilterValidationLayers();
		void FetchGlobalExtensions();
		
		VkDebugUtilsMessengerCreateInfoEXT SetupDebugMessageCallback();
	};

}