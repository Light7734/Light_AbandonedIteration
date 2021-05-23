#pragma once

#include "Base.h"

#include "Event.h"

#include <sstream>

namespace Light {

	class WindowClosedEvent : public Event
	{
	public:
		virtual std::string GetInfoLog() const override
		{
			return "WindowClosedEvent";
		}
		EVENT_TYPE(WindowClosed)
		EVENT_CATEGORY(WindowEventCategory)
	};

}