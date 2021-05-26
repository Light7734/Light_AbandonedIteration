#pragma once

// Engine
#include "Base.h"

// Platform
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#endif

// Containers
#include <array>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <map>
#include <unordered_map>
#include <unordered_set>

// Miscellaneous
#include <algorithm>
#include <functional>
#include <memory>
#include <tuple>
#include <utility>

// IO
#include <iostream>
#include <fstream>
#include <sstream>

// Multi-threading
#include <thread>
#include <atomic>

// String
#include <string>
#include <string_view>

// C-Libraries
#include <time.h>
#include <math.h>