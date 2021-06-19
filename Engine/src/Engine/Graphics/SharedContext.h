#pragma once

#include "Base.h"

namespace Light {

	class SharedContext
	{
	public:
		virtual ~SharedContext() = default;

		void DummyFunc(const std::string& value) { LT_ENGINE_TRACE(value); }
	};
}