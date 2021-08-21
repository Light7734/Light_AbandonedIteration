project "entt"

	-- Output Directories --
	location "%{wks.location}/Dependencies/entt"

	targetdir (target_dir)
	objdir    (object_dir)

	-- Compiler --
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	-- Project Files ---
	files
	{
		"entt.cpp",
		"entt.hpp",

		"%{prj.location}/build.lua",
	}
	
	--- Filters ---
	-- windows
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS",
		}

		flags { "MultiProcessorCompile" }

	-- debug
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	-- release
	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	-- distribution
	filter "configurations:Distribution"
		runtime "Release"
		optimize "full"
