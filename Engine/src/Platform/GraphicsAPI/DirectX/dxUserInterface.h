#pragma once

#include "UserInterface/UserInterface.h"

#include "Base/Base.h"

#include <d3d11.h>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

	class dxSharedContext;

	class dxUserInterface : public UserInterface
	{
	public:
		dxUserInterface(GLFWwindow* windowHandle, Ref<dxSharedContext> sharedContext);
		~dxUserInterface();

		void Begin() override;
		void End() override;

		void LogDebugData() override;
		
	private:
		void SetDarkThemeColors();
	};

}