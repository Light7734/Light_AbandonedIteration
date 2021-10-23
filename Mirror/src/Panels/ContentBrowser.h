#pragma once

#include "Panel.h"

#include <filesystem>

namespace Light {

	class ContentBrowserPanel : public Panel
	{
	private:

	public:
		ContentBrowserPanel();

		void OnUserInterfaceUpdate();

	private:
		std::filesystem::path m_CurrentDirectory;
		const std::filesystem::path m_AssetsPath;
	};

}