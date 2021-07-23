project "Mirror"

	-- Output Directories --
	location "%{wks.location}/Mirror/"

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

		"%{prj.location}/build.lua",
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
		"stb_image" ,
	}

	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LIGHT_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "On"
		
		flags { "MultiProcessorCompile" }

	-- linux
	filter "system:linux"
		defines "LIGHT_PLATFORM_LINUX"
		
		links
		{
			"dl",
			"pthread",
		}
	
	-- debug
	filter "configurations:Debug"
		defines "LIGHT_DEBUG"
		symbols "on"

	-- release 
	filter "configurations:Release"
		defines "LIGHT_RELEASE"
		optimize "on"

	-- distribution
	filter "configurations:Distribution"
		defines "LIGHT_DIST"
		optimize "on"