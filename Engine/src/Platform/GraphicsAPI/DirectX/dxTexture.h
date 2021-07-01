#pragma once

#include "Base.h"
#include "Graphics/Texture.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxTexture : public Texture
	{
	private:
		std::shared_ptr<dxSharedContext> m_Context;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ResourceView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;

	public:
		dxTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, std::shared_ptr<dxSharedContext> sharedContext);

		void Bind(unsigned int slot = 0u) override;
	};

}