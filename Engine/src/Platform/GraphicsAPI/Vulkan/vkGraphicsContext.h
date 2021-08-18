#pragma once

#include "Graphics/GraphicsContext.h"

#include "Base/Base.h"

#include <volk.h>

namespace Light {

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance m_VkInstance;
		VkDebugUtilsMessengerEXT m_VkDebugMessanger;
	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;

	private:
		bool CheckValidationLayerSupport(const std::vector<const char*>& validationLayers);

		void SetupDebugMessageCallback(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		static VKAPI_ATTR VkBool32 VKAPI_CALL vkGraphicsContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
		                                                                       VkDebugUtilsMessageTypeFlagsEXT type,
		                                                                       const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		                                                                       void* userData);
	};

}