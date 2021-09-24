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

		std::vector<uint32_t> indices;

		inline bool IsSuitableForRendering() const { return graphics.has_value() && present.has_value(); }

		operator bool() const { return IsSuitableForRendering(); };
	};

	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;

		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		inline bool IsSuitableForRendering() const { !formats.empty() && !presentModes.empty(); }

		operator bool() const { return IsSuitableForRendering(); }
	};

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		VkInstance m_VkInstance;

		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;


		VkSurfaceKHR m_Surface;

		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		std::vector<const char*> m_ValidationLayers;
		std::vector<const char*> m_GlobalExtensions;
		std::vector<const char*> m_DeviceExtensions;

		// swap chain
		VkSwapchainKHR m_Swapchain;

		std::vector<VkImage> m_SwapchainImages;
		std::vector<VkImageView> m_ImageViews;

		VkFormat m_SwapchainImageFormat;
		VkExtent2D m_SwapchainExtent;

		QueueFamilyIndices m_QueueFamilyIndices;
		SwapchainSupportDetails m_SwapChainDetails;

		GLFWwindow* m_WindowHandle;

	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;

	private:
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateWindowSurface(GLFWwindow* windowHandle);
		void CreateSwapchain();
		void CreateImageViews();


		void FilterValidationLayers();
		void FetchGlobalExtensions();
		void FetchDeviceExtensions();
		void FetchSupportedQueueFamilies();
		void FetchSwapchainSupportDetails();


		VkDebugUtilsMessengerCreateInfoEXT SetupDebugMessageCallback();
	};

}