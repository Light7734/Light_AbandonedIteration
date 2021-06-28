#pragma once

#include "Base.h"

#include <glm/glm.hpp>

namespace Light {

	class Shader;
	class SharedContext;

	class ResourceManager
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;

		std::shared_ptr<SharedContext> m_SharedContext;

		static ResourceManager* s_Context;

	public:
		static ResourceManager* Create(std::shared_ptr<SharedContext> sharedContext);

		// #todo: add geometry shader support
		static inline void CreateShader(const std::string& name, const std::string& vertexSource, const std::string& pixelSource) { s_Context->CreateShaderImpl(name, vertexSource, pixelSource); }
		static inline void LoadShader(const std::string& name, const std::string& vertexPath, const std::string& pixelPath) { s_Context->LoadShaderImpl(name, vertexPath, pixelPath); }

		static inline std::shared_ptr<Shader> GetShader(const std::string& name) { return s_Context->m_Shaders[name]; }

	private:
		ResourceManager(std::shared_ptr<SharedContext> sharedContext);

		void CreateShaderImpl(const std::string& name, const std::string& vertexSource, const std::string& pixelSource);
		void LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath);

	private:
		void ExtractShaderSource(std::string& src, const std::string& delim);
	};

}