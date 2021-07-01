#include "ltpch.h"
#include "glUserInterface.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Light {

	glUserInterface::glUserInterface(GLFWwindow* windowHandle)
	{
		// create context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// configure  io
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		// style color
		ImGui::StyleColorsDark();

		// init
		ImGui_ImplGlfw_InitForOpenGL(windowHandle, false);
		ImGui_ImplOpenGL3_Init();
	}

	glUserInterface::~glUserInterface()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void glUserInterface::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//** #TEMP_IMGUI_DEMO_TEMP# **//
		ImGui::ShowDemoWindow();
	}

	void glUserInterface::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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