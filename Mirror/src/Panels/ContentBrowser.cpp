#include "ContentBrowser.h"

#include <imgui.h>

namespace Light {

	ContentBrowserPanel::ContentBrowserPanel() :
		m_CurrentDirectory("assets"),
		m_AssetsPath("assets")
	{
	}

	void ContentBrowserPanel::OnUserInterfaceUpdate()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path("assets"))
		{
			if (ImGui::Button(" <--  "))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		for (auto& dirEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = dirEntry.path();
			Texture2D
				auto relativePathasd; = std::filesystem::relative(path, m_AssetsPath);
			std::string relativePathString = relativePath.string();

			if (dirEntry.is_directory())
			{
				if (ImGui::Button(relativePathString.c_str()))
				{
					m_CurrentDirectory /= path.filename();
				}
			}
			else
			{
				if (ImGui::Button(relativePathString.c_str()))
				{

				}
			}
		}

		ImGui::End();
	}

}