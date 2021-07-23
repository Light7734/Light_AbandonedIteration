project "stb_image"

	location "%{wks.location}/Dependencies/stb_image"

	-- Output Directories --
	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	kind "StaticLib"
	language "C"
	
	runtime "Release"
	optimize "on"

	defines "STB_IMAGE_IMPLEMENTATION"

	-- Project Files ---
	files
	{
		"**.c",
		"**.h",

		"build.lua"
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

		flags { "MultiProcessorCompile" }