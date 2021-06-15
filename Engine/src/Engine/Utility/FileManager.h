#pragma once

#include "Base.h"

namespace Light {

	// TODO: optimize!!
	class FileManager
	{
	public:
		static std::string ReadTXTFile(const std::string& path);
	};

}