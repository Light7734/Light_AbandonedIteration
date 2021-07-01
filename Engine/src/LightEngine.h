#pragma once

// Core -------------------------
#include "Core/Application.h"
#include "Core/Window.h"
// -----------------------------

// Debug 
#include "Debug/Logger.h"
// -----------------------------

// Events ----------------------
#include "Events/Event.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
// -----------------------------

// Graphics --------------------
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
// -----------------------------

// Layer -----------------------
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"
// -----------------------------

// UserInterface ---------------
#include "UserInterface/UserInterface.h"
// -----------------------------

// Utility ---------------------
#include "Utility/ResourceManager.h"
// -----------------------------

// Base -----------------------
#include "Base.h"

#ifdef LIGHT_ENTRY_POINT
	#include "EntryPoint.h"
#endif
// -----------------------------