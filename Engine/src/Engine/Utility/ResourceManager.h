#pragma once

#include "Base.h"

namespace Light {

	class Shader;
	class Texture;

	class SharedContext;

	// #todo: optimize
	class ResourceManager
	{
	private:
		static ResourceManager* s_Context;

		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;

		std::shared_ptr<SharedContext> m_SharedContext;

	public:
		static ResourceManager* Create(std::shared_ptr<SharedContext> sharedContext);

		// #todo: add geometry shader support
		static inline void CreateShader(const std::string& name, const std::string& vertexSource, const std::string& pixelSource) { s_Context->CreateShaderImpl(name, vertexSource, pixelSource); }
		static inline void LoadShader(const std::string& name, const std::string& vertexPath, const std::string& pixelPath) { s_Context->LoadShaderImpl(name, vertexPath, pixelPath); }

		static inline void LoadTexture(const std::string& name, const std::string& path, unsigned int desiredComponents = 4u) { s_Context->LoadTextureImpl(name, path, desiredComponents); }

		static inline std::shared_ptr<Shader> GetShader(const std::string& name) { return s_Context->m_Shaders[name]; }
		static inline std::shared_ptr<Texture> GetTexture(const std::string& name) { return s_Context->m_Textures[name]; }

	private:
		ResourceManager(std::shared_ptr<SharedContext> sharedContext);

		void CreateShaderImpl(const std::string& name, const std::string& vertexSource, const std::string& pixelSource);
		void LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath);

		void LoadTextureImpl(const std::string& name, const std::string& path, unsigned int desiredComponents = 4u);
	private:
		void ExtractShaderSource(std::string& src, const std::string& delim);
	};

}