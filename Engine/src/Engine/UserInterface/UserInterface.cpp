#include "ltpch.h"
#include "UserInterface.h"
#include "OpenGL/glUserInterface.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxUserInterface.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "Graphics/GraphicsContext.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

#include <imgui.h>

namespace Light {

	Scope<UserInterface> UserInterface::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateScope<glUserInterface>(windowHandle);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateScope<dxUserInterface>(windowHandle, std::dynamic_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "UserInterface::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	void UserInterface::OnInput(const Event& inputEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		switch (inputEvent.GetEventType())
		{
		//** MOUSE_EVENTS **//
		case EventType::MouseMoved:
		{
			const MouseMovedEvent& event = (const MouseMovedEvent&)inputEvent;
			ImGui::GetIO().MousePos = ImVec2(event.GetX(), event.GetY());
			return;
		}
		case EventType::ButtonPressed:
		{
			const ButtonPressedEvent& event = (const ButtonPressedEvent&)inputEvent;
			ImGui::GetIO().MouseDown[event.GetButton()] = true;
			return;
		}
		case EventType::ButtonReleased:
		{
			const ButtonReleasedEvent& event = (const ButtonReleasedEvent&)inputEvent;
			ImGui::GetIO().MouseDown[event.GetButton()] = false;
			return;
		}
		case EventType::WheelScrolled:
		{
			const WheelScrolledEvent& event = (const WheelScrolledEvent&)inputEvent;
			ImGui::GetIO().MouseWheel = event.GetOffset();
			return;
		}
		//** MOUSE_EVENTS **//
		case EventType::KeyPressed:
		{
			const KeyPressedEvent& event = (const KeyPressedEvent&)inputEvent;
			ImGui::GetIO().MouseDown[event.GetKey()] = true;
			return;
		}
		case EventType::KeyReleased:
		{
			const KeyReleasedEvent& event = (const KeyReleasedEvent&)inputEvent;
			ImGui::GetIO().MouseDown[event.GetKey()] = false;
			return;
		}
		}
	}

}