#pragma once

// core
#include "Core/Application.h"
#include "Core/Window.h"

// camera
#include "Camera/Camera.h"

// debug
#include "Debug/Logger.h"

// events
#include "Events/Event.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

// graphics
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/Framebuffer.h"

// input
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

// layer
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"

// user interface
#include "UserInterface/UserInterface.h"

// utility
#include "Utility/ResourceManager.h"

// time
#include "Time/Timer.h"

// base
#include "Base/Base.h"

// third party
#include <imgui.h>

// math
#include "Math/Random.h"

// scene
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

// entry point
#ifdef LIGHT_ENTRY_POINT
	#include "Base/EntryPoint.h"
#endif
