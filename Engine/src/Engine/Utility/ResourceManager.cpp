#include "ltpch.h"
#include "ResourceManager.h"

#include "FileManager.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Light {

	ResourceManager* ResourceManager::s_Context = nullptr;

	Scope<ResourceManager> ResourceManager::Create()
	{
		return MakeScope(new ResourceManager());
	}

	ResourceManager::ResourceManager():
		  m_Shaders{},
		  m_Textures{}
	{
		LT_ENGINE_ASSERT(!s_Context, "ResourceManager::ResourceManager: repeated singleton construction");
		s_Context = this;
	}
	
	void ResourceManager::LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath)
	{
		// check
		LT_ENGINE_ASSERT(s_Context, "ResourceManager::LoadShaderImpl: uninitliazed singleton");
		LT_ENGINE_ASSERT(!vertexPath.empty(), "ResourceManager::LoadShaderImpl: empty 'vertexPath'");
		LT_ENGINE_ASSERT(!pixelPath.empty(), "ResourceManager::LoadShaderImpl: empty 'pixelPath'");

		// load files
		BasicFileHandle vertexFile = FileManager::ReadTextFile(vertexPath);
		BasicFileHandle pixelFile = FileManager::ReadTextFile(pixelPath);

		// check
		LT_ENGINE_ASSERT(vertexFile.IsValid(), "ResourceManager::LoadShaderImpl: failed to read vertex file: {}", vertexPath);
		LT_ENGINE_ASSERT(pixelFile.IsValid(), "ResourceManager::LoadShaderImpl: failed to read vertex file: {}", pixelPath);

		// create shader
		m_Shaders[name] = Ref<Shader>(Shader::Create(vertexFile, pixelFile, GraphicsContext::GetSharedContext()));

		// free file
		vertexFile.Release();
		pixelFile.Release();
	}

	void ResourceManager::LoadTextureImpl(const std::string& name, const std::string& path, unsigned int desiredComponents /* = 4u */)
	{
		LT_ENGINE_ASSERT(s_Context, "ResourceManager::LoadShaderImpl: uninitliazed singleton");

		// load file
		ImageFileHandle imgFile = FileManager::ReadImageFile(path, desiredComponents);

		// create texture
		m_Textures[name] = Ref<Texture>(Texture::Create(imgFile.GetWidth(), imgFile.GetHeight(), imgFile.GetComponents(), imgFile.GetData(), GraphicsContext::GetSharedContext(), path) );

		// free file
		imgFile.Release();
	}

	void ResourceManager::ReleaseTextureImpl(const std::string& name)
	{
		if (!m_Textures[name])
		{
			LT_ENGINE_WARN("ResourceManager::ReleaseTextureImpl: failed to find texture named: {}", name);
			return;
		}

		m_Textures[name] = nullptr;
	}
	