#include "ltpch.h"
#include "Layer.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

namespace Light {
	
	bool Layer::OnEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		//** MOUSE_EVENTS **//
		case EventType::MouseMoved:
			return OnMouseMoved((MouseMovedEvent&)event);
		case EventType::ButtonPressed:
			return OnButtonPressed((ButtonPressedEvent&)event);
		case EventType::ButtonReleased:
			return OnButtonReleased((ButtonReleasedEvent&)event);
		case EventType::WheelScrolled:
			return OnWheelScrolled((WheelScrolledEvent&)event);

		//** KEYBOARD_EVENTS **//
		case EventType::KeyPressed:
			return OnKeyPressed((KeyPressedEvent&)event);
		case EventType::KeyReleased:
			return OnKeyReleased((KeyReleasedEvent&)event);

		//** WINDOW_EVENTS **//
		case EventType::WindowClosed:
			return OnWindowClosed((WindowClosedEvent&)event);
		case EventType::WindowResized:
			return OnWindowResized((WindowResizedEvent&)event);
		case EventType::WindowMoved:
			return OnWindowMoved((WindowMovedEvent&)event);
		case EventType::WindowLostFocus:
			return OnWindowLostFocus((WindowLostFocusEvent&)event);
		case EventType::WindowGainFocus:
			return OnWindowGainFocus((WindowGainFocusEvent&)event);
		}
	}

}