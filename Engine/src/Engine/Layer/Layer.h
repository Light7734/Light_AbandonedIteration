#pragma once

#include "Base/Base.h"

namespace Light {

	class Event;

	// mouse
	class MouseMovedEvent;
	class ButtonPressedEvent;
	class ButtonReleasedEvent;
	class WheelScrolledEvent;

	// keyboard
	class KeyPressedEvent;
	class KeyReleasedEvent;

	// window
	class WindowClosedEvent;
	class WindowResizedEvent;
	class WindowMovedEvent;
	class WindowLostFocusEvent;
	class WindowGainFocusEvent;

	class Layer
	{
	protected:
		std::string m_LayerName;

	public:
		Layer(const std::string& name);
		virtual ~Layer() = default;

		inline const std::string& GetName() const { return m_LayerName; }

		/* update */
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnUserInterfaceUpdate() {}

		virtual void OnRender() {}

		bool OnEvent(const Event& event);

	protected:
		/* mouse */
		virtual bool OnMouseMoved(const MouseMovedEvent& event) { return false; }
		virtual bool OnButtonPressed(const ButtonPressedEvent& event) { return false; }
		virtual bool OnButtonReleased(const ButtonReleasedEvent& event) { return false; }
		virtual bool OnWheelScrolled(const WheelScrolledEvent& event) { return false; }

		/* keyboard */
		virtual bool OnKeyPressed(const KeyPressedEvent& event) { return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& event) { return false; }

		/* window */
		virtual bool OnWindowClosed(const WindowClosedEvent& event) { return false; }
		virtual bool OnWindowResized(const WindowResizedEvent& event) { return false; }
		virtual bool OnWindowMoved(const WindowMovedEvent& event) { return false; }
		virtual bool OnWindowLostFocus(const WindowLostFocusEvent& event) { return false; }
		virtual bool OnWindowGainFocus(const WindowGainFocusEvent& event) { return false; }
	};

}