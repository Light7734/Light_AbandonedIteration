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

		"%{prj.location}/premake5.lua",
	}

	-- Dependencies --
	includedirs
	{
		-- Engine
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/src/Engine",
		"%{wks.location}/Engine/src/Platform/GraphicsAPI",
		"%{wks.location}/Engine/src/Platform/OS",

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "imgui/"),
		(dependenciesdir .. "imgui/backends"),
		(dependenciesdir .. "glm/"),
	}

	links
	{
		"Engine",
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