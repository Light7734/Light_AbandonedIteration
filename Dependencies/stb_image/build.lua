project "stb_image"

	-- Output Directories --
	location "%{wks.location}/Dependencies/stb_image"

	targetdir (target_dir)
	objdir    (object_dir)

	-- Compiler --
	kind "StaticLib"
	language "C"

	-- Project Files ---
	files
	{
		"stb_image.c",
		"stb_image.h",

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