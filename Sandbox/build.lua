project "Sandbox"

	-- Output Directories --
	location "%{wks.location}/Sandbox/"

	targetdir (target_dir)
	objdir    (object_dir)

	-- Compiler --
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	-- Project Files ---
	files
	{
		-- src
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",

		-- res
		"%{prj.location}/res/**",

		-- build.lua
		"%{prj.location}/build.lua",
	}

	-- Includes --
	includedirs
	{
		-- engine
		"%{include_dirs.engine}",
		"%{include_dirs.engine_platform_graphics}",
		"%{include_dirs.engine_platform_os}",
		
		-- 3rd party
		"%{include_dirs.entt}",
		"%{include_dirs.glm}",
		"%{include_dirs.imgui}",
		"%{include_dirs.imgui_backends}",
		"%{include_dirs.spdlog}",
		"%{include_dirs.stb_image}",
	}

	-- Links --
	links
	{
		"Engine",
		"GLFW",
		"GLAD",
		"ImGui",
		"stb_image" ,
		"entt",
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
		optimize "full"