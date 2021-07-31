#pragma once

#include "Base/Base.h"

namespace Light {

	struct TagComponent
	{
		std::string tag = "Unnamed";

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;

		TagComponent(const char* _tag)
			: tag(_tag)
		{
		}

		operator std::string() { return tag; }
		operator const std::string&() const { return tag; }
	};

}

