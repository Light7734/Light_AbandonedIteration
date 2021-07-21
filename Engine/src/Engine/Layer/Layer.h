#pragma once

#include "Base.h"

namespace Light {

	class Event;

	class MouseMovedEvent;
	class ButtonPressedEvent;
	class ButtonReleasedEvent;
	class WheelScrolledEvent;

	class KeyPressedEvent;
	class KeyReleasedEvent;

	class WindowClosedEvent;
	class WindowResizedEvent;
	class WindowMovedEvent;
	class WindowLostFocusEvent;
	class WindowGainFocusEvent;

	class Layer
	{
	private:
		std::string m_Name;

	public:
		Layer(const std::string& name): m_Name(name) {}
		virtual ~Layer() = default;

		inline const std::string& GetName() const { return m_Name; }

		//** UPDATES //
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnUserInterfaceUpdate() {}

		virtual void OnRender() {}

		bool OnEvent(const Event& event);

	protected:
		//** MOUSE_EVENTS //
		virtual bool OnMouseMoved(const MouseMovedEvent& event) { return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) { return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) { return false; }
		virtual bool OnWheelScrolled(const WheelScrolledEvent& event) { return false; }

		//** KEYBOARD_EVENTS **//
		virtual bool OnKeyPressed(const KeyPressedEvent& event) { return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) { return false; }

		//** WINDOW_EVENTS **/
		virtual bool OnWindowClosed(const WindowClosedEvent& event) { return false; }
		virtual bool OnWindowResized(const WindowResizedEvent& event) { return false; }
		virtual bool OnWindowMoved(const WindowMovedEvent& event) { return false; }
		virtual bool OnWindowLostFocus(const WindowLostFocusEvent& event) { return false; }
		virtual bool OnWindowGainFocus(const WindowGainFocusEvent& event) { return false; }
	};

}