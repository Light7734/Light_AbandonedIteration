project "Engine"

	-- Output Directories --
	location "%{wks.location}/Engine/"

	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	pchsource "src/Engine/ltpch.cpp"
	pchheader "ltpch.h"

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
		"%{prj.location}/src/",
		"%{prj.location}/src/Engine/",
		"%{prj.location}/src/Platform/GraphicsAPI",
		"%{prj.location}/src/Platform/OS",

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "glfw/include/"),
		(dependenciesdir .. "glad/include"),
		(dependenciesdir .. "imgui/"),
		(dependenciesdir .. "imgui/backends"),
		(dependenciesdir .. "glm/"),
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
	}
	
	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LIGHT_PLATFORM_WINDOWS"
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