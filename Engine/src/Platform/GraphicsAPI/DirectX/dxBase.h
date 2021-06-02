#pragma once

#include "Base.h"

// DirectX Call
#define DXC(x) hr = x; if(FAILED(x)) __debugbreak()