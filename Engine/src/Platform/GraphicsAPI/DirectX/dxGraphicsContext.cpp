#include "ltpch.h"
#include "dxGraphicsContext.h"
#include "dxSharedContext.h"

#include "Events/WindowEvents.h"

// forward declaration
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "UserInterface/UserInterface.h"
#include "Utility/ResourceManager.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

namespace Light {

	dxGraphicsContext::dxGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		// set 'GraphicsAPI';
		m_GraphicsAPI = GraphicsAPI::DirectX;

		// setup stuff
		SetupDeviceAndSwapChain(windowHandle);
		SetupRenderTargets();
		SetupDebugInterface();

		// create 'dxSharedContext'
		m_SharedContext = std::make_shared<dxSharedContext>(m_Device, m_DeviceContext, m_SwapChain, m_RenderTargetView);
	}

	void dxGraphicsContext::OnWindowResize(const WindowResizedEvent& event)
	{
		SetResolution(event.GetSize().x, event.GetSize().y);
	}

	void dxGraphicsContext::SetupDeviceAndSwapChain(GLFWwindow* windowHandle)
	{
		// swap chain desc
		DXGI_SWAP_CHAIN_DESC sd = { 0 };

		// buffer desc
		sd.BufferDesc.Width = 800u;
		sd.BufferDesc.Height = 600u;
		sd.BufferDesc.RefreshRate.Numerator = NULL; // :#todo
		sd.BufferDesc.RefreshRate.Denominator = NULL; // :#todo
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// sample desc (for multi sampling) #todo: implement multi-samplingz
		sd.SampleDesc.Count = 1u;
		sd.SampleDesc.Quality = 0u;

		// #todo: support swap chains with more than 1 back-buffer
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1u;

		// #todo: don't handle Windows's window with glfw, create it yourself
		sd.OutputWindow = static_cast<HWND>(glfwGetWin32Window(windowHandle));
		sd.Windowed = true;

		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		sd.Flags = NULL;

		// determine device flags
		UINT flags = NULL;
#ifdef LIGHT_DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

		// create device and swap chain
		HRESULT hr;
		DXC(D3D11CreateDeviceAndSwapChain(nullptr, 
		                                  D3D_DRIVER_TYPE_HARDWARE,
		                                  NULL,
		                                  flags,
		                                  nullptr,
		                                  NULL,
		                                  D3D11_SDK_VERSION,
		                                  &sd, 
		                                  &m_SwapChain,
		                                  &m_Device,
		                                  nullptr,
		                                  &m_DeviceContext));
	}

	void dxGraphicsContext::SetupRenderTargets()
	{
		// set primitive topology
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// create render target view 
		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;

		HRESULT hr;
		DXC(m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
		DXC(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView));

		// set render target view
		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);
	}

	void dxGraphicsContext::SetupDebugInterface()
	{
#ifdef LIGHT_DEBUG
		// configure the debug interface
		Microsoft::WRL::ComPtr<ID3D11InfoQueue> infoQueue;

		HRESULT hr;
		DXC(m_Device.As(&m_DebugInterface));
		DXC(m_DebugInterface.As(&infoQueue));

		D3D11_MESSAGE_ID hide[] =
		{
			D3D11_MESSAGE_ID_DEVICE_DRAW_SAMPLER_NOT_SET,

			// #todo: add more message ids here as needed
		};

		D3D11_INFO_QUEUE_FILTER filter = { 0 };
		filter.DenyList.NumIDs = _countof(hide);
		filter.DenyList.pIDList = hide;

		DXC(infoQueue->AddStorageFilterEntries(&filter));
#endif
	}

	void dxGraphicsContext::SetResolution(unsigned int width, unsigned int height)
	{
		// viewport
		D3D11_VIEWPORT viewport;

		viewport.Width = width;
		viewport.Height = height;

		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		// set viewport
		m_DeviceContext->RSSetViewports(1u, &viewport);
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

		// #todo: log more information
		LT_ENGINE_INFO("________________________________________");
		LT_ENGINE_INFO("dxGraphicsContext:");
		LT_ENGINE_INFO("        Renderer: {}", adapterDesc);
		LT_ENGINE_INFO("________________________________________");
	}

}