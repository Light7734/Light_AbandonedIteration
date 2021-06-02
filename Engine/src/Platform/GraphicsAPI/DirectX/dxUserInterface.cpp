#include "ltpch.h"
#include "dxUserInterface.h"

#include "dxSharedContext.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

namespace Light {

	dxUserInterface::dxUserInterface(GLFWwindow* windowHandle, void* sharedContext)
	{
		// set dxContext
		dxSharedContext* dxContext = static_cast<dxSharedContext*>(sharedContext);
		LT_ENGINE_ASSERT(dxContext, "dxUserInterface::dxUserInterface: invalid sharedContext");

		m_DeviceContext = dxContext->deviceContext;
		m_Device = dxContext->device;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
		ImGui_ImplDX11_Init(m_Device.Get(), m_DeviceContext.Get());
	}

	dxUserInterface::~dxUserInterface()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void dxUserInterface::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// TEMP
		ImGui::ShowDemoWindow();
	}

	void dxUserInterface::End()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void dxUserInterface::LogDebugData()
	{
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("UserInterface::");
		LT_ENGINE_INFO("       API    : ImGui");
		LT_ENGINE_INFO("       Version: {}", ImGui::GetVersion());
		LT_ENGINE_INFO("       GfxAPI : DirectX");
		LT_ENGINE_INFO("________________________________________");
	}

}