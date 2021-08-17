#include "ltpch.h"
#include "vkGraphicsContext.h"

#include "Graphics/Blender.h" // required for forward declaration
#include "Graphics/Buffers.h" // required for forward declaration
#include "Graphics/Renderer.h" // required for forward declaration
#include "Graphics/RenderCommand.h" // required for forward declaration

#include "UserInterface/UserInterface.h" // required for forward declaration

#include "Utility/ResourceManager.h" // required for forward declaration

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Light {

	vkGraphicsContext::vkGraphicsContext(GLFWwindow* windowHandle)
	{
		VkApplicationInfo appInfo{};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "hello vulkan";
		appInfo.applicationVersion= VK_MAKE_API_VERSION(1, 1, 1, 1);
		appInfo.pEngineName = "Light";
		appInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0u;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VKC(vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance));
	}

	vkGraphicsContext::~vkGraphicsContext()
	{
		vkDestroyInstance(m_VulkanInstance, nullptr);
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