#include "ltpch.h"
#include "vkGraphicsContext.h"

#include "Graphics/Blender.h" // required for forward declaration
#include "Graphics/Buffers.h" // required for forward declaration
#include "Graphics/Renderer.h" // required for forward declaration
#include "Graphics/RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

#include <volk.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Light {

	vkGraphicsContext::vkGraphicsContext(GLFWwindow* windowHandle)
		: m_VkInstance(NULL),
		  m_ValidationLayers { LT_VULKAN_VALIDATION_LAYERS },
		  m_GlobalExtensions{ LT_VULKAN_GLOBAL_EXTENSIONS }
	{
		// load and setup vulkan
		VKC(volkInitialize());

		FilterValidationLayers();
		FetchGlobalExtensions();
		auto debugMessageCreateInfo = SetupDebugMessageCallback();

		// application info
		VkApplicationInfo appInfo =
		{
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,

			.pApplicationName = "Vulkan Test Implementation",
			.applicationVersion = VK_MAKE_VERSION(1u, 0u, 0u),

			.pEngineName = "No Engine",
			.engineVersion = VK_MAKE_VERSION(1u, 0u, 0u),

			.apiVersion = VK_API_VERSION_1_2
		};
		
		// instance create-info
		VkInstanceCreateInfo instanceCreateInfo =
		{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = &debugMessageCreateInfo,

			.pApplicationInfo = &appInfo,

			.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size()),
			.ppEnabledLayerNames = m_ValidationLayers.data(),

			.enabledExtensionCount = static_cast<uint32_t>(m_GlobalExtensions.size()),
			.ppEnabledExtensionNames = m_GlobalExtensions.data(),

		};

		// create vulkan instance
		VKC(vkCreateInstance(&instanceCreateInfo, nullptr, &m_VkInstance));
	}

	vkGraphicsContext::~vkGraphicsContext()
	{
		vkDestroyInstance(m_VkInstance, nullptr);
	}

	void vkGraphicsContext::FetchGlobalExtensions()
	{
		// required global extensions
		uint32_t glfwExtensionsCount = 0u;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		m_GlobalExtensions.insert(m_GlobalExtensions.end(), glfwExtensions, glfwExtensions + glfwExtensionsCount);
	}

	void vkGraphicsContext::FilterValidationLayers()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_ValidationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				m_ValidationLayers.erase(std::find(m_ValidationLayers.begin(), m_ValidationLayers.end(), layerName));
				LT_ENGINE_ERROR("vkGraphicsContext::FilterValidationLayers: failed to find validation layer: {}", layerName);
			}
		}
	}

	VkDebugUtilsMessengerCreateInfoEXT vkGraphicsContext::SetupDebugMessageCallback()
	{
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo =
		{
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,

			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
							   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
							   VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,

			.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT    |
						   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
						   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pUserData = nullptr
		};

		debugMessengerCreateInfo.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		                                              VkDebugUtilsMessageTypeFlagsEXT messageType,
		                                              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		                                              void* pUserData)
		{
			std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
			return VK_FALSE;
		};

		return debugMessengerCreateInfo;
	}

	void vkGraphicsContext::LogDebugData()
	{
	}

}