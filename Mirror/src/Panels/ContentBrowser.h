#pragma once

#include "Panel.h"

#include <LightEngine.h>
#include <filesystem>

namespace Light {

class ContentBrowserPanel: public Panel
{
private:
	enum FileType
	{
		None = 0,
		Directory,
		Text,
		Image,
	};

public:
	ContentBrowserPanel();

	void OnUserInterfaceUpdate();

private:
	std::filesystem::path m_CurrentDirectory;
	const std::filesystem::path m_AssetsPath;

	// TODO: Save configuration
	uint32_t m_FileSize    = 256u;
	uint32_t m_FilePadding = 16u;

	Ref<Texture> m_DirectoryTexture;
};

} // namespace Light
