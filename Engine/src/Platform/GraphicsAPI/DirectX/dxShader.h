#pragma once

#include "Base.h"
#include "dxBase.h"
#include "Graphics/Shader.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxShader : public Shader
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;

		Microsoft::WRL::ComPtr<ID3DBlob> m_VertexBlob;
	public:
		dxShader(const std::string& vertexSource, const std::string& pixelSource, void* sharedContext);
		~dxShader();

		void Bind() override;
		void UnBind() override;

		Microsoft::WRL::ComPtr<ID3DBlob> GetVertexBlob() { return m_VertexBlob; }
	};


}