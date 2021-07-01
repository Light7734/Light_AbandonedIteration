#pragma once

#include "Base.h"
#include "Graphics/SharedContext.h"

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	// #todo:
	class dxSharedContext : public SharedContext
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device          > m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext   > m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain        > m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	public:
		dxSharedContext(Microsoft::WRL::ComPtr<ID3D11Device          > device,
		                Microsoft::WRL::ComPtr<ID3D11DeviceContext   > deviceContext,
		                Microsoft::WRL::ComPtr<IDXGISwapChain        > swapChain,
		                Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView)
			: m_Device(device), m_DeviceContext(deviceContext), m_SwapChain(swapChain), m_RenderTargetView(renderTargetView)
		{
		}

		inline Microsoft::WRL::ComPtr<ID3D11Device          > GetDevice          () { return m_Device;           }
		inline Microsoft::WRL::ComPtr<ID3D11DeviceContext   > GetDeviceContext   () { return m_DeviceContext;    }
		inline Microsoft::WRL::ComPtr<IDXGISwapChain        > GetSwapChain       () { return m_SwapChain;        }
		inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return m_RenderTargetView; }
	};

}