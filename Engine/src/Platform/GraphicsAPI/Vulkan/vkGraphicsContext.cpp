#include "ltpch.h"
#include "vkGraphicsContext.h"
#include "vkSharedContext.h"

#include "Graphics/Blender.h" // required for forward declaration
#include "Graphics/Buffers.h" // required for forward declaration
#include "Graphics/Renderer.h" // required for forward declaration
#include "Graphics/RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

#include <volk.h>

#include <GLFW/glfw3.h>

namespace Light {

	vkGraphicsContext::vkGraphicsContext(GLFWwindow* windowHandle)
		: m_VkInstance(VK_NULL_HANDLE),
		  m_PhysicalDevice(VK_NULL_HANDLE),
		  m_LogicalDevice(VK_NULL_HANDLE),
		  m_Swapchain(VK_NULL_HANDLE),
		  m_Surface(VK_NULL_HANDLE),
		  m_GraphicsQueue(VK_NULL_HANDLE),
		  m_ValidationLayers { LT_VULKAN_VALIDATION_LAYERS },
		  m_GlobalExtensions{ LT_VULKAN_GLOBAL_EXTENSIONS },
		  m_DeviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME },
		  m_WindowHandle(windowHandle)
	{
		m_SharedContext = CreateRef<vkSharedContext>();
		m_GraphicsAPI = GraphicsAPI::Vulkan;

		// load and setup vulkan
		VKC(volkInitialize());

		FilterValidationLayers();
		FetchGlobalExtensions();
		auto debugMessageCreateInfo = SetupDebugMessageCallback();

		// application info
		VkApplicationInfo appInfo
		{
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,

			.pApplicationName = "Vulkan Test Implementation",
			.applicationVersion = VK_MAKE_VERSION(1u, 0u, 0u),

			.pEngineName = "No Engine",
			.engineVersion = VK_MAKE_VERSION(1u, 0u, 0u),

			.apiVersion = VK_API_VERSION_1_2
		};

		// instance create-info
		VkInstanceCreateInfo instanceCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = &debugMessageCreateInfo,

			.pApplicationInfo = &appInfo,

			.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size()),
			.ppEnabledLayerNames = m_ValidationLayers.data(),

			.enabledExtensionCount = static_cast<uint32_t>(m_GlobalExtensions.size()),
			.ppEnabledExtensionNames = m_GlobalExtensions.data(),
		};

		// create and load vulkan instance
		VKC(vkCreateInstance(&instanceCreateInfo, nullptr, &m_VkInstance));
		volkLoadInstance(m_VkInstance);

		// pick physical device and get it rolling...
		CreateWindowSurface(windowHandle);
		PickPhysicalDevice();
		CreateLogicalDevice();
		FetchDeviceExtensions();
		FetchSwapchainSupportDetails();
		CreateSwapchain();
	}

	vkGraphicsContext::~vkGraphicsContext()
	{
		for (auto swapchainImageView : m_SwapchainImageViews)
			vkDestroyImageView(m_LogicalDevice, swapchainImageView, nullptr);

		vkDestroySwapchainKHR(m_LogicalDevice, m_Swapchain, nullptr);

		vkDestroySurfaceKHR(m_VkInstance, m_Surface, nullptr);
		vkDestroyDevice(m_LogicalDevice, nullptr);
		vkDestroyInstance(m_VkInstance, nullptr);
	}

	void vkGraphicsContext::FetchGlobalExtensions()
	{
		// fetch required global extensions
		uint32_t glfwExtensionsCount = 0u;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		// add required extensions to desired extensions
		m_GlobalExtensions.insert(m_GlobalExtensions.end(), glfwExtensions, glfwExtensions + glfwExtensionsCount);
	}

	void vkGraphicsContext::FetchDeviceExtensions()
	{
		// fetch device extensions
		uint32_t deviceExtensionsCount = 0u;
		vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &deviceExtensionsCount, nullptr);

		std::vector<VkExtensionProperties> deviceExtensions(deviceExtensionsCount);
		vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &deviceExtensionsCount, deviceExtensions.data());

		// check if device supports the required extensions
		std::set<std::string> requiredExtensions (m_DeviceExtensions.begin(), m_DeviceExtensions.end());

		for (const auto& deviceExtension : deviceExtensions)
			requiredExtensions.erase(std::string(deviceExtension.extensionName));

		if (!requiredExtensions.empty())
		{
			LT_ENGINE_CRITICAL("vkGraphicsContext::FetchDeviceExtensions: device does not supprot required extensions: ");
			
			for (auto requiredExtension : requiredExtensions)
				LT_ENGINE_CRITICAL("        {}", requiredExtension);

			LT_ENGINE_ASSERT(false, "vkGraphicsContext::FetchDeviceExtensions: aforementioned device extensinos are not supported");
		}
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

	void vkGraphicsContext::CreateLogicalDevice()
	{
		Ref<vkSharedContext> context = std::static_pointer_cast<vkSharedContext>(m_SharedContext);

		// fetch properties & features
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;

		vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
		vkGetPhysicalDeviceFeatures(m_PhysicalDevice, &deviceFeatures);

		std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;
		deviceQueueCreateInfos.reserve(m_QueueFamilyIndices.indices.size());

		// device queue create-info
		float queuePriority = 1.0f;
		for (const auto& queueFamilyIndex : m_QueueFamilyIndices.indices)
		{
			VkDeviceQueueCreateInfo deviceQueueCreateInfo
			{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,

				.queueFamilyIndex = queueFamilyIndex,
				.queueCount = 1u,

				.pQueuePriorities = &queuePriority,
			};

			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}

		// device create-info
		VkDeviceCreateInfo deviceCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,

			.queueCreateInfoCount = static_cast<uint32_t>(deviceQueueCreateInfos.size()),
			.pQueueCreateInfos = deviceQueueCreateInfos.data(),

			.enabledExtensionCount = static_cast<uint32_t>(m_DeviceExtensions.size()),
			.ppEnabledExtensionNames = m_DeviceExtensions.data(),

			.pEnabledFeatures = &deviceFeatures,
		};

		// create logical device and get it's queue
		VKC(vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_LogicalDevice));
		vkGetDeviceQueue(m_LogicalDevice, m_QueueFamilyIndices.graphics.value(), 0u, &m_GraphicsQueue);

		context->m_Device = m_LogicalDevice;
	}

	void vkGraphicsContext::CreateWindowSurface(GLFWwindow* windowHandle)
	{
		glfwCreateWindowSurface(m_VkInstance, windowHandle, nullptr, &m_Surface);
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

			VkBool32 hasPresentSupport;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, index, m_Surface, &hasPresentSupport);

			if (hasPresentSupport)
				m_QueueFamilyIndices.present = index;

			index++;
		}

		m_QueueFamilyIndices.indices = { m_QueueFamilyIndices.graphics.value(), m_QueueFamilyIndices.present.value() };
	}

	void vkGraphicsContext::FetchSwapchainSupportDetails()
	{
		// fetch device surface capabilities
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_PhysicalDevice, m_Surface, &m_SwapChainDetails.capabilities);

		// fetch device surface formats
		uint32_t formatCount = 0u;
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &formatCount, nullptr);
		LT_ENGINE_ASSERT(formatCount, "vkGraphicsContext::FetchSwapchainSupportDetails: no physical device surface format");

		m_SwapChainDetails.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &formatCount, m_SwapChainDetails.formats.data());

		// fetch device surface format modes
		uint32_t presentModeCount = 0u;
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &presentModeCount, nullptr);
		LT_ENGINE_ASSERT(presentModeCount, "vkGraphicsContext::FetchSwapchainSupportDetails: no phyiscal device surface present mode");

		m_SwapChainDetails.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &presentModeCount, m_SwapChainDetails.presentModes.data());
	}

	void vkGraphicsContext::CreateSwapchain()
	{
		// pick a decent swap chain surface format
		VkSurfaceFormatKHR swapChainSurfaceFormat{};
		for (const auto& surfaceFormat : m_SwapChainDetails.formats)
			if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				swapChainSurfaceFormat = surfaceFormat;
		
		if(swapChainSurfaceFormat.format == VK_FORMAT_UNDEFINED)
			m_SwapchainImageFormat = swapChainSurfaceFormat.format;

		// pick a decent swap chain present mode
		VkPresentModeKHR swapChainPresentMode{};
		for (const auto& presentMode : m_SwapChainDetails.presentModes)
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				swapChainPresentMode = presentMode;

		if (m_SwapChainDetails.capabilities.currentExtent.width != UINT32_MAX)
			m_SwapchainExtent = m_SwapChainDetails.capabilities.currentExtent;
		else
		{
			int width, height;
			glfwGetFramebufferSize(m_WindowHandle, &width, &height);

			m_SwapchainExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			m_SwapchainExtent.width = std::clamp(m_SwapchainExtent.width, m_SwapChainDetails.capabilities.minImageExtent.width,
			                                                              m_SwapChainDetails.capabilities.maxImageExtent.width);

			m_SwapchainExtent.height = std::clamp(m_SwapchainExtent.height, m_SwapChainDetails.capabilities.minImageExtent.height,
			                                                                m_SwapChainDetails.capabilities.maxImageExtent.height);
		}

		uint32_t imageCount = m_SwapChainDetails.capabilities.minImageCount + 1;
		if (m_SwapChainDetails.capabilities.maxImageCount > 0 && imageCount > m_SwapChainDetails.capabilities.maxImageCount)
			imageCount = m_SwapChainDetails.capabilities.maxImageCount;

		// swapchain create-info
		VkSwapchainCreateInfoKHR swapchainCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,

			.surface = m_Surface,

			.minImageCount = imageCount,
			.imageFormat = swapChainSurfaceFormat.format,
			.imageColorSpace = swapChainSurfaceFormat.colorSpace,
			.imageExtent = m_SwapchainExtent,
			.imageArrayLayers = 1u,
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			.imageSharingMode = m_QueueFamilyIndices.graphics.value() == m_QueueFamilyIndices.present.value() ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,

			.queueFamilyIndexCount = m_QueueFamilyIndices.graphics.value() == m_QueueFamilyIndices.present.value() ? 0u : 2u,
			.pQueueFamilyIndices = m_QueueFamilyIndices.graphics.value() == m_QueueFamilyIndices.present.value() ? nullptr : m_QueueFamilyIndices.indices.data(),
			.preTransform = m_SwapChainDetails.capabilities.currentTransform,
			.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			.presentMode = swapChainPresentMode,
			.clipped = VK_TRUE,
			.oldSwapchain = VK_NULL_HANDLE,
		};

		VKC(vkCreateSwapchainKHR(m_LogicalDevice, &swapchainCreateInfo, nullptr, &m_Swapchain));
		
		vkGetSwapchainImagesKHR(m_LogicalDevice, m_Swapchain, &imageCount, nullptr);
		m_SwapchainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_LogicalDevice, m_Swapchain, &imageCount, m_SwapchainImages.data());
	}

	void vkGraphicsContext::CreateImageViews()
	{
		m_SwapchainImageViews.resize(m_SwapchainImages.size());

		for (int i = 0; i < m_SwapchainImages.size(); i++)
		{
			// image view create-info
			VkImageViewCreateInfo imageViewCreateInfo
			{
				.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				.image = m_SwapchainImages[i],
				.viewType = VK_IMAGE_VIEW_TYPE_2D,
				.format = m_SwapchainImageFormat,
				.components
				{
					.r = VK_COMPONENT_SWIZZLE_IDENTITY,
					.g = VK_COMPONENT_SWIZZLE_IDENTITY,
					.b = VK_COMPONENT_SWIZZLE_IDENTITY,
					.a = VK_COMPONENT_SWIZZLE_IDENTITY,
				},
				.subresourceRange
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
					.baseMipLevel = 0u,
					.levelCount = 0u,
					.baseArrayLayer = 0u,
					.layerCount = 0u,
				}
			};

			VKC(vkCreateImageView(m_LogicalDevice, &imageViewCreateInfo, nullptr, &m_SwapchainImageViews[i]));
		}
	}

	VkDebugUtilsMessengerCreateInfoEXT vkGraphicsContext::SetupDebugMessageCallback()
	{
		// debug messenger create-info
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo
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