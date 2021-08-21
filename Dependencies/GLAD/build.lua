project "GLAD"

	-- Output Directories --
	location "%{wks.location}/Dependencies/GLAD"

	targetdir (target_dir)
	objdir    (object_dir)

	-- Compiler --
	kind "StaticLib"
	language "C"

	-- Project Files ---
	files
	{
		"src/glad.c",
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",

		"%{prj.location}/build.lua",
	}
	
	-- Includes --
	includedirs
	{
		"%{prj.location}/include/"
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
