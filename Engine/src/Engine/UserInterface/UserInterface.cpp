#include "ltpch.h"
#include "UserInterface.h"
#include "OpenGL/glUserInterface.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxUserInterface.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "Events/Event.h"
#include "Events/CharEvent.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

#include "Graphics/GraphicsContext.h"

#include "Input/KeyCodes.h"

#include <imgui.h>

namespace Light {

	Scope<UserInterface> UserInterface::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
	{
		Scope<UserInterface> scopeUserInterface = nullptr;


		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			scopeUserInterface = CreateScope<glUserInterface>();
			break;

		case GraphicsAPI::DirectX: LT_WIN(
			scopeUserInterface = CreateScope<dxUserInterface>();)
			break;

		default:
			LT_ENGINE_ASSERT(false, "UserInterface::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}

		scopeUserInterface->Init(windowHandle, sharedContext);
		return std::move(scopeUserInterface);
	}


	void UserInterface::Init(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
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
		if (std::filesystem::exists("user_gui_layout.ini"))
			io.IniFilename = "user_gui_layout.ini";
		else
			io.IniFilename = "default_gui_layout.ini";

		// style
		ImGui::StyleColorsDark();

		PlatformImplementation(windowHandle, sharedContext);

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

		io.Fonts->AddFontFromFileTTF("res/Fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("res/Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

		SetDarkThemeColors();
	}

	void UserInterface::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

}