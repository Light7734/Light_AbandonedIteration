#pragma once

#include "Graphics/Shader.h"

#include "Base/Base.h"

#include "Utility/FileManager.h"

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
		dxShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile, Ref<dxSharedContext> sharedContext);
		~dxShader();

		void Bind() override;
		void UnBind() override;

		inline Microsoft::WRL::ComPtr<ID3DBlob> GetVertexBlob() { return m_VertexBlob; }
	};

}