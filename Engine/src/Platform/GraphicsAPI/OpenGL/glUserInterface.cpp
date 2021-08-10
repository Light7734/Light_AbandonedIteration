
#include "ltpch.h"
#include "glUserInterface.h"

#include "Input/KeyCodes.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Light {

	glUserInterface::glUserInterface(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		// create context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// configure  io
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.ConfigFlags |= ImGuiBackendFlags_PlatformHasViewports;
		io.ConfigFlags |= ImGuiBackendFlags_RendererHasViewports;

		// #todo: handle this in a better way
		if (std::filesystem::exists("user_gui_layout.ini"))
			io.IniFilename = "user_gui_layout.ini";
		else
			io.IniFilename = "default_gui_layout.ini";

		// style color
		ImGui::StyleColorsDark();

		// init
		ImGui_ImplGlfw_InitForOpenGL(windowHandle, false);
		ImGui_ImplOpenGL3_Init();

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

		io.FontDefault = io.Fonts->AddFontFromFileTTF("res/Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

	}

	glUserInterface::~glUserInterface()
	{
		// #todo: handle this in a better way
		ImGuiIO& io = ImGui::GetIO();

		if (io.IniFilename == "default_gui_layout.ini")
			io.IniFilename = "user_gui_layout.ini";

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void glUserInterface::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* #TEMP_IMGUI_DEMO_TEMP# */
		ImGui::ShowDemoWindow();
	}

	void glUserInterface::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(m_WindowHandle);
	}

	void glUserInterface::LogDebugData()
	{
		// #todo: improve
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("UserInterface::");
		LT_ENGINE_INFO("       API    : ImGui");
		LT_ENGINE_INFO("       Version: {}", ImGui::GetVersion());
		LT_ENGINE_INFO("  GraphicsAPI : OpenGL");
		LT_ENGINE_INFO("________________________________________");
	}

}