#include "ltpch.h"
#include "dxGraphicsContext.h"

// Required for forward declaration
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"
#include "UserInterface/UserInterface.h" 

#include <glfw/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>

#include "dxSharedContext.h"

namespace Light {

	dxGraphicsContext::dxGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		m_GraphicsAPI = GraphicsAPI::DirectX;

		HRESULT hr;

		DXGI_SWAP_CHAIN_DESC sd = { 0 };
		sd.OutputWindow = static_cast<HWND>(glfwGetWin32Window(windowHandle));

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1u;

		sd.BufferDesc.Width = 800u;
		sd.BufferDesc.Height = 600u;
		sd.BufferDesc.RefreshRate.Denominator = NULL;
		sd.BufferDesc.RefreshRate.Numerator = NULL;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		sd.SampleDesc.Count = 1u;
		sd.SampleDesc.Quality = 0u;

		sd.Windowed = true;
		sd.Flags = NULL;
		
		UINT flags = NULL;

#ifdef LIGHT_DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		DXC(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		                              NULL, flags, NULL, NULL, D3D11_SDK_VERSION,
		                              &sd, &m_SwapChain, &m_Device, NULL, &m_DeviceContext));
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
		DXC(m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
		DXC(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView));
		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);

		Microsoft::WRL::ComPtr<ID3D11InfoQueue> infoQueue;

		DXC(m_Device.As(&debugInterface));
		DXC(debugInterface.As(&infoQueue));

		D3D11_MESSAGE_ID hide[] =
		{
			D3D11_MESSAGE_ID_DEVICE_DRAW_SAMPLER_NOT_SET,

			// #todo: add more message IDs here as needed
		};

		D3D11_INFO_QUEUE_FILTER filter;
		memset(&filter, 0, sizeof(filter));
		filter.DenyList.NumIDs = _countof(hide);
		filter.DenyList.pIDList = hide;
		infoQueue->AddStorageFilterEntries(&filter);


		D3D11_VIEWPORT viewport;

		viewport.Width = 800.0f;
		viewport.Height = 600.0f;

		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		m_DeviceContext->RSSetViewports(1u, &viewport);

		dxSharedContext* sharedContext = new dxSharedContext({m_DeviceContext, m_SwapChain, m_RenderTargetView, m_Device});
		m_SharedContext = sharedContext;


	}

	void dxGraphicsContext::OnWindowResize(const WindowResizedEvent& event)
	{

	}

	void dxGraphicsContext::LogDebugData()
	{
		// locals 
		IDXGIDevice* DXGIDevice;
		IDXGIAdapter* DXGIAdapter;
		DXGI_ADAPTER_DESC DXGIAdapterDesc;

		m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);
		DXGIDevice->GetAdapter(&DXGIAdapter);
		DXGIAdapter->GetDesc(&DXGIAdapterDesc);

		// get the adapter's description
		char DefChar = ' ';
		char ch[180];
		WideCharToMultiByte(CP_ACP, 0, DXGIAdapterDesc.Description, -1, ch, 180, &DefChar, NULL);
		std::string adapterDesc(ch);

		// release memory
		DXGIDevice->Release();
		DXGIAdapter->Release();

		// log info // #todo: log more information
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("dxGraphicsContext:");
		LT_ENGINE_INFO("        Renderer: {}", adapterDesc);
		LT_ENGINE_INFO("________________________________________");
	}

}