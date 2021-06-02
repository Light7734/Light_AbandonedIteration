#pragma once

#include "Base.h"
#include "dxBase.h"
#include "UserInterface/UserInterface.h"

struct GLFWwindow;

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxUserInterface : public UserInterface
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;

	public:
		dxUserInterface(GLFWwindow* windowHandle, void* sharedContext);
		~dxUserInterface();

		void Begin() override;
		void End() override;

		void LogDebugData() override;
	};

}