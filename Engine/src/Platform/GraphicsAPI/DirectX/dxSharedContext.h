#pragma once

#include "Base.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	struct dxSharedContext
	{
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	};

}