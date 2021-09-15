#pragma once

#include "Graphics/GraphicsContext.h"
#include "Base/Base.h"

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Light {

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphics;
		std::optional<uint32_t> present;

		std::vector<std::optional<uint32_t>> indices{ graphics, present };

		inline bool IsSuitableForRendering() const
		{
			return graphics.has_value() && present.has_value();
		}

		operator bool() const { return IsSuitableForRendering(); };
	};

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		VkInstance m_VkInstance;

		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;

		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		VkSurfaceKHR m_Surface;

		std::vector<const char*> m_ValidationLayers;
		std::vector<const char*> m_GlobalExtensions;

		QueueFamilyIndices m_QueueFamilyIndices;

	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;

	private:
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateWindowSurface(GLFWwindow* windowHandle);

		void FilterValidationLayers();
		void FetchGlobalExtensions();
		void FetchSupportedQueueFamilies();

		VkDebugUtilsMessengerCreateInfoEXT SetupDebugMessageCallback();
	};

}