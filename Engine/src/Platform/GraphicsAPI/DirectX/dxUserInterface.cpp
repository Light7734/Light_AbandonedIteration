#include "ltpch.h"
#include "dxUserInterface.h"
#include "dxSharedContext.h"

#include "Input/KeyCodes.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

namespace Light {

	dxUserInterface::dxUserInterface(GLFWwindow* windowHandle, Ref<dxSharedContext> sharedContext)
	{
		// create context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// configure io
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.ConfigFlags |= ImGuiBackendFlags_PlatformHasViewports;
		io.ConfigFlags |= ImGuiBackendFlags_RendererHasViewports;

		// #todo: handle this in a better way
		if(std::filesystem::exists("user_gui_layout.ini"))
			io.IniFilename = "user_gui_layout.ini";
		else 
			io.IniFilename = "default_gui_layout.ini";

		// style
		ImGui::StyleColorsDark();

		// init
		ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
		ImGui_ImplDX11_Init(sharedContext->GetDevice().Get(), sharedContext->GetDeviceContext().Get());

		// keyboard map
		io.KeyMap[ImGuiKey_Tab] = Key::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = Key::LeftArrow;
		io.KeyMap[ImGuiKey_RightArrow] = Key::RightArrow;
		io.KeyMap[ImGuiKey_UpArrow] = Key::UpArrow;
		io.KeyMap[ImGuiKey_DownArrow] = Key::DownArrow;
		io.KeyMap[ImGuiKey_PageUp] = Key::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = Key::PageDown;
		io.KeyMap[ImGuiKey_Home] = Key::Home;
		io.KeyMap[ImGuiKey_End] = Key::End;
		io.KeyMap[ImGuiKey_Insert] = Key::Insert;
		io.KeyMap[ImGuiKey_Delete] = Key::Delete;
		io.KeyMap[ImGuiKey_Backspace] = Key::BackSpace;
		io.KeyMap[ImGuiKey_Space] = Key::Space;
		io.KeyMap[ImGuiKey_Enter] = Key::Enter;
		io.KeyMap[ImGuiKey_Escape] = Key::Escape;
		io.KeyMap[ImGuiKey_KeyPadEnter] = Key::Enter;
		io.KeyMap[ImGuiKey_A] = Key::A;
		io.KeyMap[ImGuiKey_C] = Key::C;
		io.KeyMap[ImGuiKey_V] = Key::V;
		io.KeyMap[ImGuiKey_X] = Key::X;
		io.KeyMap[ImGuiKey_Y] = Key::Y;
		io.KeyMap[ImGuiKey_Z] = Key::Z;
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

		/* #TEMP_IMGUI_DEMO_TEMP# */
		ImGui::ShowDemoWindow();
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