#pragma once

#include "Base.h"

#include <ostream>

#include <vector>

namespace Light {

	enum class EventType
	{
		None = 0,

		// input
		MouseMoved, ButtonPressed, ButtonReleased, // mouse
		KeyPressed, KeyReleased, // keyboard

		// window
		WindowMoved, WindowResized, WindowClosed,
	};

	enum EventCategory
	{
		None = 0,

		WindowEventCategory = BIT(0),
		InputEventCategory = BIT(1),
		KeyboardEventCategory = BIT(2),
		MouseEventCategory = BIT(3),
	};

#define EVENT_TYPE(type) EventType GetEventType() const override { return EventType::##type; }
#define EVENT_CATEGORY(eCategory) inline bool IsInCategory(EventCategory category) const override { return (eCategory) & category; } 

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string GetInfoLog() const = 0;
		virtual bool IsInCategory(EventCategory category) const = 0;

		friend std::ostream & operator<<(std::ostream & os, const Event& e)
		{
			return os << e.GetInfoLog();
		}
	};

}