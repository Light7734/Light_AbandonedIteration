#include "ltpch.h"
#include "ResourceManager.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <stb_image.h>

namespace Light {

	ResourceManager* ResourceManager::s_Context = nullptr;

	Scope<ResourceManager> ResourceManager::Create(Ref<SharedContext> sharedContext)
	{
		return MakeScope(new ResourceManager(sharedContext));
	}

	ResourceManager::ResourceManager(Ref<SharedContext> sharedContext)
		: m_SharedGraphicsContext(sharedContext),
		  m_Shaders{},
		  m_Textures{}
	{
		LT_ENGINE_ASSERT(!s_Context, "ResourceManager::ResourceManager: an instance of 'ResourceManager' already exists, do not construct this class!");
		s_Context = this;

		stbi_set_flip_vertically_on_load(true);
	}
	
	void ResourceManager::LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath)
	{
		std::vector<uint8_t> vertexFile, pixelFile;

		std::ifstream file;
		std::ios_base::openmode mode = std::ios_base::in;
		
		// read vertex shader file
		file.open(vertexPath.c_str(), mode);
		LT_ENGINE_ASSERT(file, "ResourceManager::LoadShaderImpl: failed to load vertex shader at path: {}", vertexPath);
		if (file)
		{
			file.seekg(0, std::ios::end);
			vertexFile.resize(static_cast<size_t>(file.tellg()));
			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char*>(vertexFile.data()), vertexFile.size());
			vertexFile.resize(static_cast<size_t>(file.gcount()));
			file.close();
		}

		// read pixel shader file
		file.open(pixelPath.c_str(), mode);
		LT_ENGINE_ASSERT(file, "ResourceManager::LoadShaderImpl: failed to load vertex shader at path: {}", vertexPath);
		if (file)
		{
			file.seekg(0, std::ios::end);
			pixelFile.resize(static_cast<size_t>(file.tellg()));
			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char*>(pixelFile.data()), pixelFile.size());
			pixelFile.resize(static_cast<size_t>(file.gcount()));
			file.close();
		}

		// create shader
		m_Shaders[name] = Ref<Shader>(Shader::Create(vertexFile, pixelFile, vertexPath, pixelPath, m_SharedGraphicsContext));
	}

	void ResourceManager::LoadTextureImpl(const std::string& name, const std::string& path, unsigned int desiredComponents /* = 4u */)
	{
		// load image
		int width, height, components;
		unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &components, desiredComponents);
		
		// check
		LT_ENGINE_ASSERT(pixels, "ResourceManager::LoadTextureImpl: failed to load texture <{}>, 'path': {}", name, path);
		if (components != desiredComponents)
		{
			LT_ENGINE_WARN("ResourceManager::LoadTextureImpl: image file compoenents != 'desiredComponents' ({} - {})", components, desiredComponents);
			LT_ENGINE_WARN("ResourceManager::LoadTextureImpl: <{}> 'path': {}", name, path);
		}

		// create texture
		m_Textures[name] = Ref<Texture>(Texture::Create(width, height, components, pixels, m_SharedGraphicsContext));
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

}