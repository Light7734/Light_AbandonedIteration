#include "ltpch.h"
#include "Input.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"

#include <imgui.h>

namespace Light {

	Input* Input::s_Context = nullptr;

	Scope<Input> Input::Create()
	{
		return MakeScope(new Input);
	}

	Input::Input()
		: m_KeyboadKeys{},
		  m_MouseButtons{},
		  m_MousePosition{},
		  m_MouseDelta{},
		  m_MouseWheelDelta{},
		  m_UserInterfaceEvents(true),
		  m_GameEvents(true)
	{
		LT_ENGINE_ASSERT(!s_Context, "Input::Input: an instance of 'Input' already exists, do not construct this class!");
		s_Context = this;

		RestartInputState();
	}

	void Input::ReceiveUserInterfaceEventsImpl(bool receive, bool toggle /* = false */)
	{
		m_UserInterfaceEvents = toggle ? !m_UserInterfaceEvents : receive;
	}

	void Input::ReceieveGameEventsImpl(bool receive, bool toggle /*= false*/)
	{
		bool prev = m_GameEvents;
		m_GameEvents = toggle ? !m_UserInterfaceEvents : receive;

		if(m_GameEvents != prev)
			RestartInputState();
	}

	void Input::RestartInputState()
	{
		m_KeyboadKeys.fill(false);
		m_MouseButtons.fill(false);

		m_MousePosition = glm::vec2(0.0f);
		m_MouseDelta = glm::vec2(0.0f);
		m_MouseWheelDelta = 0.0f;
	}

	void Input::OnEvent(const Event& inputEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		switch (inputEvent.GetEventType())
		{
			//** MOUSE_EVENTS **//
		case EventType::MouseMoved:
		{
			const MouseMovedEvent& event = (const MouseMovedEvent&)inputEvent;

			if (m_GameEvents)
			{
				m_MouseDelta = event.GetPosition() - m_MousePosition;
				m_MousePosition = event.GetPosition();
			}

			if(m_UserInterfaceEvents)
				ImGui::GetIO().MousePos = ImVec2(event.GetX(), event.GetY());

			return;
		}
		case EventType::ButtonPressed:
		{
			const ButtonPressedEvent& event = (const ButtonPressedEvent&)inputEvent;

			if(m_GameEvents)
				m_MouseButtons[event.GetButton()] = true;

			if (m_UserInterfaceEvents)
				ImGui::GetIO().MouseDown[event.GetButton()] = true;

			return;
		}
		case EventType::ButtonReleased:
		{
			const ButtonReleasedEvent& event = (const ButtonReleasedEvent&)inputEvent;

			if (m_GameEvents)
				m_MouseButtons[event.GetButton()] = false;

			if (m_UserInterfaceEvents)
				ImGui::GetIO().MouseDown[event.GetButton()] = false;

			return;
		}
		case EventType::WheelScrolled:
		{
			const WheelScrolledEvent& event = (const WheelScrolledEvent&)inputEvent;

			if (m_GameEvents)
				m_MouseWheelDelta = event.GetOffset();

			if (m_UserInterfaceEvents)
				ImGui::GetIO().MouseWheel = event.GetOffset();

			return;
		}
		//** MOUSE_EVENTS **//
		case EventType::KeyPressed:
		{
			const KeyPressedEvent& event = (const KeyPressedEvent&)inputEvent;

			if (m_GameEvents)
				m_KeyboadKeys[event.GetKey()] = true;

			if (m_UserInterfaceEvents)
				ImGui::GetIO().KeysDown[event.GetKey()] = true;

			return;
		}
		case EventType::KeyReleased:
		{
			const KeyReleasedEvent& event = (const KeyReleasedEvent&)inputEvent;

			if (m_GameEvents)
				m_KeyboadKeys[event.GetKey()] = false;

			if (m_UserInterfaceEvents)
				ImGui::GetIO().KeysDown[event.GetKey()] = false;

			return;
		}
		}
	}

}