#include "ContentBrowser.h"

#include <LightEngine.h>
#include <imgui.h>

namespace Light {

ContentBrowserPanel::ContentBrowserPanel()
    : m_CurrentDirectory("Assets"), m_AssetsPath("Assets")
{
	// ResourceManager::LoadTexture("_Assets_Directory", "EngineResources/Icons/Asset_Directory");
	// m_DirectoryTexture = ResourceManager::GetTexture("_Assets_Directory");
}

void ContentBrowserPanel::OnUserInterfaceUpdate()
{
	ImGui::Begin("Content Browser");

	if (m_CurrentDirectory != std::filesystem::path("Assets"))
	{
		if (ImGui::Button(" <--  "))
		{
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}


	ImVec2 regionAvail   = ImGui::GetContentRegionAvail();
	uint32_t cellSize    = m_FileSize + m_FilePadding;
	uint32_t columnCount = std::clamp(static_cast<uint32_t>(std::floor(regionAvail.x / cellSize)), 1u, 64u);

	if (ImGui::BeginTable("ContentBrowser", columnCount))
	{
		for (auto& dirEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			ImGui::TableNextColumn();
			LT_ENGINE_TRACE("File: ", dirEntry.path().string());
			FileType assetType;
			std::string extension = dirEntry.path().extension().string();

			// TODO: Tidy up
			assetType = extension.empty()   ? FileType::Directory :
			            extension == ".txt" ? FileType::Text :
			            extension == ".png" ? FileType::Image :
                                              FileType::None;

			if (assetType == FileType::None)
			{
				LT_ENGINE_ERROR("Unsupported file exetnsion: {}", extension);
				return;
			}

			const auto& path = dirEntry.path();
			{
				auto relativePath              = std::filesystem::relative(path, m_AssetsPath);
				std::string relativePathString = relativePath.string();

				switch (assetType)
				{
				case FileType::Directory:
					if (ImGui::Button(relativePathString.c_str(), ImVec2(m_FileSize, m_FileSize)))
					{
						m_CurrentDirectory /= path.filename();
					}
					ImGui::Text("Test");
					break;
				case FileType::Image:
					if (ImGui::Button(relativePathString.c_str(), ImVec2(m_FileSize, m_FileSize)))
					{
					}
					break;
				case FileType::Text:
					if (ImGui::Button(relativePathString.c_str(), ImVec2(m_FileSize, m_FileSize)))
					{
					}
				default:
					break;
				}
			}
		}

		ImGui::EndTable();
	}
	ImGui::DragInt("Size", (int*)&m_FileSize, 32u, 512u);
	ImGui::DragInt("Padding", (int*)&m_FilePadding, 32u, 512u);
	ImGui::End();
}

} // namespace Light
