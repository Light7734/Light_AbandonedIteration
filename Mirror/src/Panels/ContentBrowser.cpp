#include "ContentBrowser.hpp"

#include <LightEngine.hpp>
#include <imgui.h>

namespace Light {

AssetBrowserPanel::AssetBrowserPanel()
    : m_CurrentDirectory("Assets"), m_AssetsPath("Assets")
{
	ResourceManager::LoadTexture("_Assets_Directory", "EngineResources/Icons/Asset_Directory.png");
	ResourceManager::LoadTexture("_Assets_Image", "EngineResources/Icons/Asset_Image.png");
	ResourceManager::LoadTexture("_Assets_Text", "EngineResources/Icons/Asset_Text.png");
	m_DirectoryTexture = ResourceManager::GetTexture("_Assets_Directory");
	m_ImageTexture     = ResourceManager::GetTexture("_Assets_Image");
	m_TextTexture      = ResourceManager::GetTexture("_Assets_Text");
}

void AssetBrowserPanel::OnUserInterfaceUpdate()
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
		m_DirectoryTexture->Bind(0u);
		for (auto& dirEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			AssetType assetType;
			std::string extension = dirEntry.path().extension().string();

			// TODO: Tidy up
			assetType = extension.empty() ? AssetType::Directory :

			            extension == ".txt"  ? AssetType::Text :
			            extension == ".glsl" ? AssetType::Text :

			            extension == ".png" ? AssetType::Image :

                                              AssetType::None;

			// Unsupported asset type
			if (assetType == AssetType::None)
			{
				continue;
			}

			const auto& path               = dirEntry.path();
			auto relativePath              = std::filesystem::relative(path, m_AssetsPath);
			std::string relativePathString = relativePath.string();

			// Button
			ImGui::TableNextColumn();
			ImGui::PushID(path.c_str());
			switch (assetType)
			{
			case AssetType::Directory:
				if (ImGui::ImageButton(m_DirectoryTexture->GetTexture(), ImVec2(m_FileSize, m_FileSize), ImVec2 { 0.0f, 0.0f }, ImVec2 { 1.0f, 1.0f }, 0, ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f }, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }))
				{
					m_CurrentDirectory /= path.filename();
				}
				break;

			case AssetType::Image:
				if (ImGui::ImageButton(m_ImageTexture->GetTexture(), ImVec2(m_FileSize, m_FileSize), ImVec2 { 0.0f, 0.0f }, ImVec2 { 1.0f, 1.0f }, 0, ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f }, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }))
				{
				}
				break;

			case AssetType::Text:
				if (ImGui::ImageButton(m_TextTexture->GetTexture(), ImVec2(m_FileSize, m_FileSize), ImVec2 { 0.0f, 0.0f }, ImVec2 { 1.0f, 1.0f }, 0, ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f }, ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }))
				{
				}
				break;

			default:
				break;
			}
			// Label
			ImGui::Text("%s", path.filename().c_str());
			ImGui::PopID();
		}

		ImGui::EndTable();
	}
	ImGui::End();
}

} // namespace Light
