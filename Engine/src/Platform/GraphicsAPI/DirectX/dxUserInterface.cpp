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

	dxUserInterface::dxUserInterface(GLFWwindow* windowHandle, std::shared_ptr<dxSharedContext> sharedContext)
	{
		// create context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// configure io
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		// style
		ImGui::StyleColorsDark();

		// init
		ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
		ImGui_ImplDX11_Init(sharedContext->device.Get(), sharedContext->deviceContext.Get());
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

		//* TEMP_ IMGUI DEBUG WINDOW _TEMP *//
		ImGui::ShowDemoWindow();
	}

	void dxUserInterface::End()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void dxUserInterface::LogDebugData()
	{
		// #todo: improve
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("UserInterface::");
		LT_ENGINE_INFO("       API    : ImGui");
		LT_ENGINE_INFO("       Version: {}", ImGui::GetVersion());
		LT_ENGINE_INFO("       GfxAPI : DirectX");
		LT_ENGINE_INFO("________________________________________");
	}

}