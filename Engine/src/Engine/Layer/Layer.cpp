#include "Layer.hpp"

#include "Events/CharEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyboardEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/WindowEvents.hpp"

namespace Light {

Layer::Layer(const std::string& name)
    : m_LayerName(name)
{
}

bool Layer::OnEvent(const Event& event)
{
	switch (event.GetEventType())
	{
	/* mouse */
	// cursor
	case EventType::MouseMoved:
		return OnMouseMoved((MouseMovedEvent&)event);
	// button
	case EventType::ButtonPressed:
		return OnButtonPressed((ButtonPressedEvent&)event);
	case EventType::ButtonReleased:
		return OnButtonReleased((ButtonReleasedEvent&)event);
	// wheel
	case EventType::WheelScrolled:
		return OnWheelScrolled((WheelScrolledEvent&)event);

	/* keyboard */
	// key
	case EventType::KeyPressed:
		return OnKeyPressed((KeyPressedEvent&)event);
	case EventType::KeyRepeated:
		return OnKeyRepeat((KeyRepeatEvent&)event);
	case EventType::KeyReleased:
		return OnKeyReleased((KeyReleasedEvent&)event);
	// char
	case EventType::SetChar:
		return OnSetChar((SetCharEvent&)event);

	/* window */
	// termination
	case EventType::WindowClosed:
		return OnWindowClosed((WindowClosedEvent&)event);
	// size/position
	case EventType::WindowResized:
		return OnWindowResized((WindowResizedEvent&)event);
	case EventType::WindowMoved:
		return OnWindowMoved((WindowMovedEvent&)event);
	// focus
	case EventType::WindowLostFocus:
		return OnWindowLostFocus((WindowLostFocusEvent&)event);
	case EventType::WindowGainFocus:
		return OnWindowGainFocus((WindowGainFocusEvent&)event);
	}
}

} // namespace Light