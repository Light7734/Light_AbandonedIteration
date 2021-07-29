#pragma once

/* engine */
#include "Base/Base.h"

/* windows */
#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
	#undef NOMINMAX
#endif

/* containers */
#include <array>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <map>
#include <unordered_map>
#include <unordered_set>

/* misc */
#include <algorithm>
#include <functional>
#include <memory>
#include <tuple>
#include <utility>

/* input/output */
#include <iostream>
#include <fstream>
#include <sstream>

/* multi threading */
#include <thread>
#include <atomic>

/* string */
#include <string>
#include <string_view>

/* filesystem */
#include <filesystem>

/* c libraries */
#include <time.h>
#include <math.h>