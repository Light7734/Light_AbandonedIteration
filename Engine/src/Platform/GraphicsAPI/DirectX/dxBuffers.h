#pragma once

#include "Base.h"
#include "dxBase.h"
#include "Graphics/Buffers.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxVertexBuffer : public VertexBuffer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;

		D3D11_MAPPED_SUBRESOURCE m_Map;
		
		unsigned int m_Stride;
	public:
		dxVertexBuffer(float* vertices, unsigned int stride, unsigned int count, void* sharedContext);
		~dxVertexBuffer();

		void* Map() override;
		void UnMap() override;

		void Bind() override;
		void UnBind() override;
	};

	class dxIndexBuffer : public IndexBuffer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	public:
		dxIndexBuffer(unsigned int* indices, unsigned int count, void* sharedContext);
		~dxIndexBuffer();

		void Bind() override;
		void UnBind() override;
	};

}