#include "ltpch.h"
#include "FileManager.h"

namespace Light {

	std::string FileManager::ReadTXTFile(const std::string& path)
	{
		// initialize
		std::ifstream stream(path);
		std::stringstream ss;
		std::string line;

		// check
		LT_ENGINE_ASSERT(!path.empty(), "FileManager::ReadTXTFile: path is empty");
		LT_ENGINE_ASSERT(stream.is_open(), "FileManager::ReadTXTFile: invalid path: {}", path);

		// read
		while (std::getline(stream, line))
			ss << line << '\n';

		return ss.str();
	}

}