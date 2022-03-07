#pragma once

#include "Panel.h"

#include <LightEngine.h>
#include <filesystem>

namespace Light {

class AssetBrowserPanel: public Panel
{
private:
	enum AssetType
	{
		None = 0,
		Directory,
		Text,
		Image,
	};

public:
	AssetBrowserPanel();

	void OnUserInterfaceUpdate();

private:
	std::filesystem::path m_CurrentDirectory;
	const std::filesystem::path m_AssetsPath;

	// TODO: Save configuration
	uint32_t m_FileSize    = 128u;
	uint32_t m_FilePadding = 8u;

	Ref<Texture> m_DirectoryTexture;
	Ref<Texture> m_ImageTexture;
	Ref<Texture> m_TextTexture;
};

} // namespace Light
