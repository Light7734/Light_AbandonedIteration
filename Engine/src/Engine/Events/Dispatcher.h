#pragma once

#include "Base.h"

#include "Event.h"

#include "Layer/Layer.h"

namespace Light {

	class Dispatcher
	{
	public:
		void Dispatch(Event& event, std::vector<Layer*>::iterator begin, std::vector<Layer*>::iterator end)
		{
			switch (event.GetEventType())
			{
			case EventType::MouseMoved:
				for (auto it = begin; it != end; it++)
					if ((*it)->OnMouseMoved((MouseMovedEvent&)event)) return;
				return;
			case EventType::ButtonPressed:
				for (auto it = begin; it != end; it++)
					if ((*it)->OnButtonPressed((ButtonPressedEvent&)event)) return;
				return;
			case EventType::ButtonReleased:
				for (auto it = begin; it != end; it++)
					if ((*it)->OnButtonReleased((ButtonReleasedEvent&)event)) return;
				return;
			case EventType::KeyPressed:
				for (auto it = begin; it != end; it++)
					if ((*it)->OnKeyPressed((KeyPressedEvent&)event)) return;
				return;
			case EventType::KeyReleased:
				for (auto it = begin; it != end; it++)
					if ((*it)->OnKeyReleased((KeyReleasedEvent&)event)) return;
				return;
			}
		}
	};

}