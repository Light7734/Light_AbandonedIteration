#pragma once

#include "Base.h"
#include "Graphics/Buffers.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	//* VERTEX BUFFER *//
	class dxVertexBuffer : public VertexBuffer
	{
	private:
		std::shared_ptr<dxSharedContext> m_Context;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		D3D11_MAPPED_SUBRESOURCE m_Map;
		
		unsigned int m_Stride;

	public:
		dxVertexBuffer(float* vertices, unsigned int stride, unsigned int count, std::shared_ptr<dxSharedContext> sharedContext);
		~dxVertexBuffer();

		void* Map() override;
		void UnMap() override;

		void Bind() override;
		void UnBind() override;
	};

	//* INDEX BUFFER *//
	class dxIndexBuffer : public IndexBuffer
	{
	private:
		std::shared_ptr<dxSharedContext> m_Context;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;

	public:
		dxIndexBuffer(unsigned int* indices, unsigned int count, std::shared_ptr<dxSharedContext> sharedContext);
		~dxIndexBuffer();

		void Bind() override;
		void UnBind() override;
	};

}