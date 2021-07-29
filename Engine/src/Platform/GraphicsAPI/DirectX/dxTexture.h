#pragma once

#include "Graphics/Texture.h"

#include "Base/Base.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxTexture : public Texture
	{
	private:
		Ref<dxSharedContext> m_Context;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture2D;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;

	public:
		dxTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, Ref<dxSharedContext> sharedContext);

		void Bind(unsigned int slot = 0u) override;
	};

}