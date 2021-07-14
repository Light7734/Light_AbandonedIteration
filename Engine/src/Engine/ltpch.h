#pragma once

//** ENGINE **//
#include "Base.h"

//** PLATFORM SPECIFIC **//
// windows
#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
	#undef NOMINMAX
#endif

//** CONTAINERS **//
#include <array>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <map>
#include <unordered_map>
#include <unordered_set>

//** MISCELLANEOUS **//
#include <algorithm>
#include <functional>
#include <memory>
#include <tuple>
#include <utility>

//** INPUT_OUTPUT **//
#include <iostream>
#include <fstream>
#include <sstream>

//** MULTI_THREADING **//
#include <thread>
#include <atomic>

//** STRING **//
#include <string>
#include <string_view>

//** FILESYSTEM  **//
#include <filesystem>

//** C_LIBRARIES **//
#include <time.h>
#include <math.h>