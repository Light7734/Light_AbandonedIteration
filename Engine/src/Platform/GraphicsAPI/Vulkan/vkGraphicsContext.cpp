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

	}

	vkGraphicsContext::~vkGraphicsContext()
	{
		// DestroyDebugUtilsMessengerEXT(m_VkInstance, m_VkDebugMessanger, nullptr);
		vkDestroyInstance(m_VkInstance, nullptr);
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

			LT_DEBUG_TRAP(); // #todo: throw vkException
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