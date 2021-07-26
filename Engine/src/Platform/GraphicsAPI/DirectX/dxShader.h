#pragma once

#include "Base.h"
#include "Graphics/Shader.h"

#include <glm/glm.hpp>

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxShader : public Shader
	{
	private:
		Ref<dxSharedContext> m_Context;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		Microsoft::WRL::ComPtr<ID3DBlob> m_VertexBlob;

	public:
		dxShader(const std::string& vertexSource, const std::string& pixelSource, Ref<dxSharedContext> sharedContext);
		~dxShader();

		void Bind() override;
		void UnBind() override;

		void SetUniformMat4(const std::string& name, const glm::mat4& value) override;

		Microsoft::WRL::ComPtr<ID3DBlob> GetVertexBlob() { return m_VertexBlob; }
	};

}