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
		: m_VkInstance(VK_NULL_HANDLE),
		  m_PhysicalDevice(VK_NULL_HANDLE),
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

		// create and vulkan instance
		VKC(vkCreateInstance(&instanceCreateInfo, nullptr, &m_VkInstance));
		volkLoadInstance(m_VkInstance);

		// specify devices
		PickPhysicalDevice();
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

		// add required extensions to desired extensions
		m_GlobalExtensions.insert(m_GlobalExtensions.end(), glfwExtensions, glfwExtensions + glfwExtensionsCount);
	}

	void vkGraphicsContext::PickPhysicalDevice()
	{
		// fetch physical devices
		uint32_t deviceCount = 0u;
		vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);
		LT_ENGINE_ASSERT(deviceCount, "vkGraphicsContext::PickPhysicalDevice: failed to find a GPU with vulkan support");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, devices.data());

		// select most suitable physical device
		uint8_t highestDeviceScore = 0u;
		for (const auto& device : devices)
		{
			uint32_t deviceScore = 0u;

			// fetch properties & features
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;

			vkGetPhysicalDeviceProperties(device, &properties);
			vkGetPhysicalDeviceFeatures(device, &features);

			// geometry shader is needed for rendering
			if (!features.geometryShader)
				continue;

			// discrete gpu is favored
			if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				deviceScore += 1000;

			deviceScore += properties.limits.maxImageDimension2D;

			// more suitable device found
			if (deviceScore > highestDeviceScore)
			{
				m_PhysicalDevice = device;

				// check if device supports required queue families
				FetchSupportedQueueFamilies();
				if (!m_QueueFamilyIndices)
					m_PhysicalDevice = VK_NULL_HANDLE;
				else
					highestDeviceScore = deviceScore;
			}
		}

		LT_ENGINE_ASSERT(m_PhysicalDevice, "vkGraphicsContext::PickPhysicalDevice: failed to find suitable GPU for vulkan");
	}

	void vkGraphicsContext::FilterValidationLayers()
	{
		// fetch available layers
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		// remove requested layers that are not supported
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

	void vkGraphicsContext::FetchSupportedQueueFamilies()
	{
		m_QueueFamilyIndices = {};

		// fetch queue families
		uint32_t queueFamilyCount = 0u;
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, queueFamilies.data());

		// find queue family indices
		uint32_t index = 0u;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				m_QueueFamilyIndices.graphics = index;

			index++;
		}
	}

	VkDebugUtilsMessengerCreateInfoEXT vkGraphicsContext::SetupDebugMessageCallback()
	{
		// debug messenger create-info
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

		// debug message callback
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

	// #todo: implement
	void vkGraphicsContext::LogDebugData()
	{
		LT_ENGINE_ERROR("vkGraphicsContext::LogDebugData: NO_IMPLEMENTATION");
	}

}