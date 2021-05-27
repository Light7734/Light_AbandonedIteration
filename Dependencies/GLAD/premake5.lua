project "GLAD"

	location "%{wks.location}/Dependencies/GLAD"

	-- Output Directories --
	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	kind "StaticLib"
	language "C"

	-- Project Files ---
	files
	{
		"**.c",
		"**.h",

		"premake5.lua"
	}
	
	-- Dependencies --
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
		optimize "on"