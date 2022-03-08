#pragma once

// core
#include "Core/Application.hpp"
#include "Core/Window.hpp"

// camera
#include "Camera/Camera.hpp"

// debug
#include "Debug/Logger.hpp"

// events
#include "Events/Event.hpp"
#include "Events/KeyboardEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/WindowEvents.hpp"

// graphics
#include "Graphics/Framebuffer.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"

// input
#include "Input/Input.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/MouseCodes.hpp"

// layer
#include "Layer/Layer.hpp"
#include "Layer/LayerStack.hpp"

// user interface
#include "UserInterface/UserInterface.hpp"

// utility
#include "Utility/ResourceManager.hpp"

// time
#include "Time/Timer.hpp"

// base
#include "Base/Base.hpp"

// third party
#include <imgui.h>

// math
#include "Math/Random.hpp"

// scene
#include "Scene/Components.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Scene.hpp"

// entry point
#ifdef LIGHT_ENTRY_POINT
	#include "Base/EntryPoint.hpp"
#endif
