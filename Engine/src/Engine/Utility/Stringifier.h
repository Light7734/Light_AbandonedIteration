#pragma once

#include "Base.h"

namespace Light {

	class Stringifier
	{
	public:
		static std::string glDebugMsgSeverity(unsigned int severity);
		static std::string glDebugMsgSource(unsigned int source);
		static std::string glDebugMsgType(unsigned int type);

		static std::string spdlogLevel(unsigned int level);
	};

}