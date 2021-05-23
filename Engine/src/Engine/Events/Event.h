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

#define EVENT_TYPE(type) EventType GetEventType() const override { return EventType::##type; }

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string GetInfoLog() const = 0;

		friend std::ostream & operator<<(std::ostream & os, const Event& e)
		{
			return os << e.GetInfoLog();
		}
	};

}