#pragma once

#include "Base.h"
#include "UserInterface/UserInterface.h"

struct GLFWwindow;

#include <d3d11.h>
#include <wrl.h>

namespace Light {

	class dxSharedContext;

	class dxUserInterface : public UserInterface
	{
	public:
		dxUserInterface(GLFWwindow* windowHandle, std::shared_ptr<dxSharedContext> sharedContext);
		~dxUserInterface();

		void Begin() override;
		void End() override;

		void LogDebugData() override;
	};

}