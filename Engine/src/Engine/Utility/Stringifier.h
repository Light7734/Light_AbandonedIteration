#pragma once
#ifndef LIGHT_STRINGIFIER_H
#define LIGHT_STRINGIFIER_H

#include "Base/Base.h"

namespace Light {

	enum class GraphicsAPI;

	// #todo: improve
	class Stringifier
	{
	public:
		static std::string glDebugMsgSeverity(unsigned int severity);
		static std::string glDebugMsgSource(unsigned int source);
		static std::string glDebugMsgType(unsigned int type);

		static std::string vkErrorCode(int errorCode);
		static std::string vkDebugMessageSeverity(uint32_t severity);
		static std::string vkDebugMessageType(uint32_t type);

		static std::string spdlogLevel(unsigned int level);

		static std::string GraphicsAPIToString(GraphicsAPI api);

	};

}

#endif