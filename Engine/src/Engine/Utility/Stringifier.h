#pragma once

#include "Base/Base.h"

namespace Light {

	enum class GraphicsAPI;

	class Stringifier
	{
	public:
		static std::string glDebugMsgSeverity(unsigned int severity);
		static std::string glDebugMsgSource(unsigned int source);
		static std::string glDebugMsgType(unsigned int type);

		static std::string spdlogLevel(unsigned int level);

		static std::string GraphicsAPIToString(GraphicsAPI api);
	};

}