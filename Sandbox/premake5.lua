project "Sandbox"

	-- Output Directories --
	location "%{wks.location}/Sandbox/"

	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	-- Project Files ---
	files
	{
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/**.lua",
	}

	-- Dependencies --
	includedirs
	{
		-- Engine
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/src/Engine",

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "glm/"),
	}

	links
	{
		"Engine",
	}

	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LT_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "On"

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