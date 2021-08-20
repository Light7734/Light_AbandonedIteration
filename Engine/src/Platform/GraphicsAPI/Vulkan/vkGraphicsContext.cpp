#include "ltpch.h"
#include "vkGraphicsContext.h"

#include "Graphics/Blender.h" // required for forward declaration
#include "Graphics/Buffers.h" // required for forward declaration
#include "Graphics/Renderer.h" // required for forward declaration
#include "Graphics/RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	vkGraphicsContext::vkGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle),
		  m_VkInstance(VK_NULL_HANDLE),
		  m_VkPhysicalDevice(VK_NULL_HANDLE),
		  m_VkDebugMessanger(VK_NULL_HANDLE)
	{
		VKC(volkInitialize());

		// app info
		VkApplicationInfo appInfo{};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "LightEngine - vulkan support";
		appInfo.applicationVersion= VK_MAKE_API_VERSION(1, 1, 1, 1);
		appInfo.pEngineName = "Light";
		appInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// instance info
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// extensions
		uint32_t glfwExtensionCount = 0u;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		createInfo.enabledExtensionCount = (uint32_t)extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		// validation layers
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		LT_ENGINE_ASSERT(CheckValidationLayerSupport(validationLayers), "vkGraphicsContext::vkGraphicsContext: validation layers requested but not available");

		createInfo.enabledLayerCount = (uint32_t)validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();

		// debug message
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		SetupDebugMessageCallback(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		// create and load!
		VKC(vkCreateInstance(&createInfo, nullptr, &m_VkInstance));
		volkLoadInstance(m_VkInstance);

		CreateSurface();

		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain();
	}

	vkGraphicsContext::~vkGraphicsContext()
	{
		vkDestroySwapchainKHR(m_VkLogicalDevice, m_SwapChain, nullptr);
		vkDestroySurfaceKHR(m_VkInstance, m_Surface, nullptr);
		vkDestroyDevice(m_VkLogicalDevice, nullptr);
		vkDestroyInstance(m_VkInstance, nullptr);
	}

	void vkGraphicsContext::PickPhysicalDevice()
	{
		uint32_t deviceCount = 0u;
		vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, physicalDevices.data());

		for(const auto& device : physicalDevices)
		{
			if(IsDeviceSuitable(device))
			{
				m_VkPhysicalDevice = device;
				break;
			}
		}

		LT_ENGINE_ASSERT(m_VkPhysicalDevice, "vkGraphicsContext::PickPhysicalDevice: no suitable phyical device found");
	}

	void vkGraphicsContext::CreateLogicalDevice()
	{
		QueueFamilyIndices indices = FindQueueFamilies(m_VkPhysicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		
		float queuePriority = 1.0f;
		for(uint32_t queueFamily : uniqueQueueFamilies){
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1u;
			queueCreateInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = queueCreateInfos.size();
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		static std::vector<const char*> extensionNames{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		createInfo.enabledExtensionCount = 1u;
		createInfo.ppEnabledExtensionNames = extensionNames.data();

		VKC(vkCreateDevice(m_VkPhysicalDevice, &createInfo, nullptr, &m_VkLogicalDevice));

		vkGetDeviceQueue(m_VkLogicalDevice, indices.graphicsFamily.value(), 0, &m_VkGraphicsQueue);
		vkGetDeviceQueue(m_VkLogicalDevice, indices.presentFamily.value(), 0, &m_VkPresentQueue);
	}

	void vkGraphicsContext::CreateSurface()
	{
		VKC(glfwCreateWindowSurface(m_VkInstance, m_WindowHandle, nullptr, &m_Surface));
	}

	void vkGraphicsContext::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_VkPhysicalDevice);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
			imageCount = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		
		createInfo.surface = m_Surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = FindQueueFamilies(m_VkPhysicalDevice);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if(indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = true;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		VKC(vkCreateSwapchainKHR(m_VkLogicalDevice, &createInfo, nullptr, &m_SwapChain));

		vkGetSwapchainImagesKHR(m_VkLogicalDevice, m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_VkLogicalDevice, m_SwapChain, &imageCount, m_SwapChainImages.data());

		m_SwapChainFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}

	VkSurfaceFormatKHR vkGraphicsContext::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for(const auto& format : availableFormats)
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return format;

		return availableFormats[0];
	}

	VkPresentModeKHR vkGraphicsContext::chooseSwapPresentMode(const std::vector<VkPresentModeKHR >& availablePresentModes)
	{
		for (const auto& presentMode : availablePresentModes)
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return presentMode;

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D vkGraphicsContext::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
			return capabilities.currentExtent;

		int width, height;
		glfwGetFramebufferSize(m_WindowHandle, &width, &height);

		VkExtent2D actualExtent = {
			(uint32_t)width,
			(uint32_t)height
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.width = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}

	QueueFamilyIndices vkGraphicsContext::FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0u;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for(const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.graphicsFamily = i;

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);

			if (presentSupport)
				indices.presentFamily = i;

			if (indices)
				break;
		}
		
		return indices;
	}

	SwapChainSupportDetails vkGraphicsContext::QuerySwapChainSupport(const VkPhysicalDevice& device)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.capabilities);

		uint32_t formatCount = 0u;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.formats.data());


		uint32_t presentModeCount = 0u;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &formatCount, details.presentModes.data());

		return details;
	}

	bool vkGraphicsContext::IsDeviceSuitable(const VkPhysicalDevice& device)
	{
		return FindQueueFamilies(device) && CheckDeviceExtensionSupport(device) && QuerySwapChainSupport(device);
	}

	bool vkGraphicsContext::CheckDeviceExtensionSupport(const VkPhysicalDevice& device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		for(const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);


		return requiredExtensions.empty();
	}

	bool vkGraphicsContext::CheckValidationLayerSupport(const std::vector<const char*>& validationLayers)
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for(const char* layerName : validationLayers) 
		{
			bool layerFound = false;

			for(const auto& layerProperties : availableLayers)
			{
				if(!strcmp(layerProperties.layerName, layerName))
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
				return false;
		}

		return true;
	}

	void vkGraphicsContext::SetupDebugMessageCallback(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		                             VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    |
		                             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		                             VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT    |
		                         VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		                         VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;

		createInfo.pfnUserCallback = vkGraphicsContext::DebugCallback;
		createInfo.pUserData = nullptr;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL vkGraphicsContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	                                                                VkDebugUtilsMessageTypeFlagsEXT type,
	                                                                const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	                                                                void* userData)
	{
		// #todo: improve
		switch (severity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			LT_ENGINE_TRACE("vkMessageCallback: Severity: {} :: Type: {} :: ID: {}",
			                Stringifier::vkDebugMessageSeverity(severity),
			                Stringifier::vkDebugMessageType(type),
			                callbackData->messageIdNumber);

			LT_ENGINE_TRACE("        msg: {}", callbackData->pMessage);
			
			return VK_FALSE;

		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			LT_ENGINE_INFO("vkMessageCallback: Severity: {} :: Type: {} :: ID: {}",
				Stringifier::vkDebugMessageSeverity(severity),
				Stringifier::vkDebugMessageType(type),
				callbackData->messageIdNumber);
			LT_ENGINE_INFO("        msg: {}", callbackData->pMessage);

			return VK_FALSE;

		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			LT_ENGINE_WARN("vkMessageCallback: Severity: {} :: Type: {} :: ID: {}",
				Stringifier::vkDebugMessageSeverity(severity),
				Stringifier::vkDebugMessageType(type),
				callbackData->messageIdNumber);
			LT_ENGINE_WARN("        msg: {}", callbackData->pMessage);

			return VK_FALSE;

		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			LT_ENGINE_CRITICAL("vkMessageCallback: Severity: {} :: Type: {} :: ID: {}",
				Stringifier::vkDebugMessageSeverity(severity),
				Stringifier::vkDebugMessageType(type),
				callbackData->messageIdNumber);
			LT_ENGINE_CRITICAL("        msg: {}", callbackData->pMessage);

			return VK_FALSE;
		}
	}

	void vkGraphicsContext::LogDebugData()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("GraphicsContext::");
		LT_ENGINE_INFO("        API     : Vulkan");
		LT_ENGINE_INFO("        Extensions:");
		for (const auto& extension : extensions) {
			LT_ENGINE_INFO("                {}: v{}", extension.extensionName, extension.specVersion);
		}
		LT_ENGINE_INFO("________________________________________");
	}

}