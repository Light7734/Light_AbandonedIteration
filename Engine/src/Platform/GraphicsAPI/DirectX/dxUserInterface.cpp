#include "dxUserInterface.h"
#include "dxSharedContext.h"

#include "Input/KeyCodes.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

namespace Light {

	void dxUserInterface::PlatformImplementation(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
	{
		ImGuiIO& io = ImGui::GetIO();
		Ref<dxSharedContext> context = std::dynamic_pointer_cast<dxSharedContext>(sharedContext);

		ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
		ImGui_ImplDX11_Init(context->GetDevice().Get(), context->GetDeviceContext().Get());
	}

	dxUserInterface::~dxUserInterface()
	{
		// #todo: handle this in a better way
		ImGuiIO& io = ImGui::GetIO();

		if (io.IniFilename == "default_gui_layout.ini")
			io.IniFilename = "user_gui_layout.ini";

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void dxUserInterface::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void dxUserInterface::End()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	void dxUserInterface::LogDebugData()
	{
		// #todo: improve
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("UserInterface::");
		LT_ENGINE_INFO("       API    : ImGui");
		LT_ENGINE_INFO("       Version: {}", ImGui::GetVersion());
		LT_ENGINE_INFO("  GraphicsAPI : DirectX");
		LT_ENGINE_INFO("________________________________________");
	}

}