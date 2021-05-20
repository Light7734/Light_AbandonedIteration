project "Engine"

	-- Output Directories --
	location "../Engine/"

	targetdir ("../bin/"     .. outputdir)
	objdir    ("../bin-int/" .. outputdir)

	-- Compiler --
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	-- Project Files ---
	files
	{
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.lua",
	}
	
	-- Dependencies --
		-- NILL --
	
	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LT_PLATFORM_WINDOWS"
		systemversion "latest"

	-- debug
	filter "configurations:Debug"
		defines "LT_DEBUG"
		symbols "on"

	-- release
	filter "configurations:Release"
		defines "LT_RELEASE"
		optimize "on"

	-- distribution
	filter "configurations:Distribution"
		defines "LT_DIST"
		optimize "on"