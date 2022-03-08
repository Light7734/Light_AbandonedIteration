#pragma once

#include "Base/Base.hpp"
#include "Event.hpp"

#include <sstream>

namespace Light {

class SetCharEvent: public Event
{
private:
	const unsigned int m_Character;

public:
	SetCharEvent(unsigned int character)
	    : m_Character(character)
	{
	}

	inline int GetCharacter() const { return m_Character; }

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "CharSet: " << m_Character;
		return ss.str();
	}
	EVENT_TYPE(SetChar)
	EVENT_CATEGORY(InputEventCategory | KeyboardEventCategory)
};

} // namespace Light