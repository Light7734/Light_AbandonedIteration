#include "FileManager.hpp"

#include <stb_image.h>

namespace Light {

BasicFileHandle FileManager::ReadTextFile(const std::string& path)
{
	// parse path info
	std::string name      = path.substr(0, path.find('.') + -1);
	std::string extension = path.substr(path.find('.') + 1);

	// open file
	std::ifstream file(path.c_str(), std::ios_base::in | std::ios_base::binary);

	// check
	if (!file)
	{
		LOG(warn, "Failed to load text file: {}", path);
		file.close();
		return NULL;
	}

	// fetch file size
	file.seekg(0, std::ios::end);
	uint32_t size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (!size)
		LOG(warn, "Empty text file: {}", path);

	// read file
	uint8_t* data = new uint8_t[size];
	file.read(reinterpret_cast<char*>(data), size);

	file.close();
	return BasicFileHandle(data, size, path, name, extension);
}

ImageFileHandle FileManager::ReadImageFile(const std::string& path, int32_t desiredComponents)
{
	// parse path info
	std::string name      = path.substr(0, path.find('.') + -1);
	std::string extension = path.substr(path.find('.') + 1);

	// load image
	int32_t width = 0, height = 0, fetchedComponents = 0;
	uint8_t* pixels = stbi_load(path.c_str(), &width, &height, &fetchedComponents, desiredComponents);

	// check
	if (!pixels)
		LOG(warn, "Failed to load image file: <{}>", path);
	else if (fetchedComponents != desiredComponents)
		LOG(warn, "Mismatch of fetched/desired components: <{}> ({}/{})", name + '.' + extension, fetchedComponents, desiredComponents);

	return ImageFileHandle(pixels, width * height, path, name, extension, width, height, fetchedComponents, desiredComponents);
}

} // namespace Light
