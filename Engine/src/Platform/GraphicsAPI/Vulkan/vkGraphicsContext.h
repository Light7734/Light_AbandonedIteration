#pragma once

#include "Graphics/GraphicsContext.h"

#include "Base/Base.h"

#include <optional>

#include <volk.h>

namespace Light {

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		inline operator bool() const {
			bool b1 = graphicsFamily.has_value();
			bool b2 = presentFamily.has_value();
			return b1 && b2;
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		inline operator bool() const { return !formats.empty() && !presentModes.empty(); }
	};

	class vkGraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance m_VkInstance;
		VkPhysicalDevice m_VkPhysicalDevice;

		VkDevice m_VkLogicalDevice;
		VkQueue m_VkGraphicsQueue;
		VkQueue m_VkPresentQueue;

		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		VkFormat m_SwapChainFormat;
		VkExtent2D m_SwapChainExtent;

		VkDebugUtilsMessengerEXT m_VkDebugMessanger;
		VkSurfaceKHR m_Surface;

	public:
		vkGraphicsContext(GLFWwindow* windowHandle);
		~vkGraphicsContext();

		void LogDebugData() override;

	private:
		void PickPhysicalDevice();

		void CreateLogicalDevice();

		void CreateSurface();

		void CreateSwapChain();

		void CreateImageViews();

		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR >& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

		SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device);

		bool IsDeviceSuitable(const VkPhysicalDevice& device);

		bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);

		bool CheckValidationLayerSupport(const std::vector<const char*>& validationLayers);

		void SetupDebugMessageCallback(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		static VKAPI_ATTR VkBool32 VKAPI_CALL vkGraphicsContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
		                                                                       VkDebugUtilsMessageTypeFlagsEXT type,
		                                                                       const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		                                                                       void* userData);
	};

}