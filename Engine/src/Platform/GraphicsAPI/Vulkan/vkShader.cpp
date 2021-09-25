#include "ltpch.h"
#include "vkShader.h"

#include <volk.h>

namespace Light {

	vkShader::vkShader(const std::vector<uint8_t>& vertexBlob, const std::vector<uint8_t>& pixelBlob, const std::string& vertexFileName, const std::string& pixelFileName, Ref<vkSharedContext> sharedContext)
		: m_Context(sharedContext)
	{

		// compile hlsl into spir-v
		ShaderConductor::Compiler::ResultDesc vertexResult = CompileHLSL(vertexBlob, vertexFileName, Shader::Stage::VERTEX);
		ShaderConductor::Compiler::ResultDesc pixelResult = CompileHLSL(pixelBlob, pixelFileName, Shader::Stage::PIXEL);

		// shader modules create-info
		VkShaderModuleCreateInfo vertexShaderModuleCreateInfo =
		{
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.codeSize = vertexResult.target.Size(), // :#todo_now
			.pCode = reinterpret_cast<const uint32_t*>(vertexResult.target.Data())// :#todo_now	
		};

		VkShaderModuleCreateInfo pixelShaderModuleCreateInfo =
		{
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.codeSize = pixelResult.target.Size(), // :#todo_now
			.pCode = reinterpret_cast<const uint32_t*>(pixelResult.target.Data())// :#todo_now	
		};


		// create shader modules
		VKC(vkCreateShaderModule(m_Context->GetDevice(), &vertexShaderModuleCreateInfo, nullptr, &m_VSModule));
		VKC(vkCreateShaderModule(m_Context->GetDevice(), &pixelShaderModuleCreateInfo, nullptr, &m_PSModule));


		// shader stages create-info
		VkPipelineShaderStageCreateInfo vertexShaderCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_VERTEX_BIT,
			.module = m_VSModule,
			.pName = "main",
		};
		
		VkPipelineShaderStageCreateInfo pixelShaderCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = m_PSModule,
			.pName = "main",
		};

		vkDestroyShaderModule(m_Context->GetDevice(), m_VSModule, nullptr);
		vkDestroyShaderModule(m_Context->GetDevice(), m_PSModule, nullptr);
	}

	vkShader::~vkShader()
	{
	}

	void vkShader::Bind()
	{

	}

	void vkShader::UnBind()
	{

	}

	ShaderConductor::Compiler::ResultDesc vkShader::CompileHLSL(std::vector<uint8_t> blob, std::string fileName, Shader::Stage stage)
	{
		// check
		LT_ENGINE_ASSERT(!blob.empty(), "vkShader::CompileHLSL: 'blob' is empty");
		LT_ENGINE_ASSERT(!fileName.empty(), "vkShader::CompileHLSL: 'fileName' is empty");
		LT_ENGINE_ASSERT(stage, "vkShader::CompileHLSL: 'stage' is invalid: None");

		// compiler options
		ShaderConductor::Compiler::Options options
		{
			.packMatricesInRowMajor = true,
			.enableDebugInfo = true,
			.disableOptimizations = true,
			.inheritCombinedSamplerBindings = true,
			.shaderModel = { 4, 5 }
		};

		// compiler target descriptor
		ShaderConductor::Compiler::TargetDesc targetDesc
		{
			.language = ShaderConductor::ShadingLanguage::SpirV,
		};

		// compiler source descriptor
		std::string source(reinterpret_cast<char*>(blob.data()), blob.size());
		ShaderConductor::Compiler::SourceDesc sourceDesc
		{
			.source = source.c_str(), // :#todo, can't we just cast blob.data to c_str?
			.fileName = fileName.c_str(),
			.entryPoint = "main",
			.stage = stage == Shader::Stage::VERTEX ? ShaderConductor::ShaderStage::VertexShader :
					 stage == Shader::Stage::PIXEL ? ShaderConductor::ShaderStage::PixelShader :
													 ShaderConductor::ShaderStage::GeometryShader,
			.defines = nullptr,
			.numDefines = 0u,
			.loadIncludeCallback = nullptr
		};

		// compilation result
		ShaderConductor::Compiler::ResultDesc result = ShaderConductor::Compiler::Compile(sourceDesc, options, targetDesc);

		
		// log info
		LT_ENGINE_INFO("_______________________________________");
		LT_ENGINE_INFO("Compiled with ShaderConductor:");
		LT_ENGINE_INFO("		hasError: {}", result.hasError);
		LT_ENGINE_INFO("		isText: {}", result.isText);

		if (result.errorWarningMsg.Size() != 0u)
		{
			const char* errorStr = reinterpret_cast<const char*>(result.errorWarningMsg.Data());
			LT_ENGINE_ERROR("				errorWarningMsg: \n{}", errorStr);
		}
		if (result.target.Size() != 0u)
		{
			const char* targetStr = reinterpret_cast<const char*>(result.target.Data());
			LT_ENGINE_INFO("				target: \n{}", targetStr);
		}
		LT_ENGINE_INFO("_______________________________________");
		
		return result;
	}

}