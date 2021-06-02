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

		DXGI_SWAP_CHAIN_DESC sd = { 0 };
		sd.BufferCount = 1u;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = glfwGetWin32Window(m_WindowHandle);
		sd.SampleDesc.Count = 1u;
		sd.Windowed = true;

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		                              NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
		                              &sd, &m_SwapChain, &m_Device, NULL, &m_DeviceContext);

		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
		m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer);
		m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView);
		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);


		D3D11_VIEWPORT viewport;

		viewport.Width = 800.0f;
		viewport.Height = 600.0f;

		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		m_DeviceContext->RSSetViewports(1u, &viewport);

		dxSharedContext* sharedContext = new dxSharedContext({m_DeviceContext, m_SwapChain, m_RenderTargetView});
		m_SharedContext = sharedContext;

		// log some information about dx context //
// locals 
		IDXGIDevice* DXGIDevice;
		IDXGIAdapter* DXGIAdapter;
		DXGI_ADAPTER_DESC DXGIAdapterDesc;

		// initialize Locals
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
		LT_ENGINE_INFO("dxGraphicsContext:");
		LT_ENGINE_INFO("        Renderer: {}", adapterDesc);
	}

	void dxGraphicsContext::OnWindowResize(const WindowResizedEvent& event)
	{

	}

	void dxGraphicsContext::LogDebugData()
	{

	}

}