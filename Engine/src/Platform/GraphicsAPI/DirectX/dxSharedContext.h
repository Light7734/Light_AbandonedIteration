#pragma once

#include "Base.h"
#include "Graphics/SharedContext.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	// #todo:
	class dxSharedContext : public SharedContext
	{
	public:
		dxSharedContext(Microsoft::WRL::ComPtr<ID3D11Device> _device, 
		                Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext,
		                Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain,
		                Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView)
			: device(_device), deviceContext(_deviceContext), swapChain(_swapChain), renderTargetView(_renderTargetView)
		{
		}

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	};

}