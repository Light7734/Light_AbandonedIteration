#pragma once

#include "Base/Base.h"
#include "Graphics/Shader.h"

#include "vkSharedContext.h"

#include <ShaderConductor/ShaderConductor.hpp>

namespace Light {

	class vkShader : public Shader
	{
	private:
		Ref<vkSharedContext> m_Context;
		VkShaderModule m_VSModule, m_PSModule;

		std::array<VkPipelineShaderStageCreateInfo, 2> m_PipielineShaderStageCreateInfo;

	public:
		vkShader(const std::vector<uint8_t>& vertexBlob, const std::vector<uint8_t>& pixelBlob, const std::string& vertexFileName, const std::string& pixelFileName, Ref<vkSharedContext> sharedContext);
		~vkShader();

		void Bind() override;
		void UnBind() override;

	private:
		ShaderConductor::Compiler::ResultDesc CompileHLSL(std::vector<uint8_t> blob, std::string fileName, Shader::Stage stage);
	};

}