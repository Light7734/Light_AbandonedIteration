project "Engine"

	-- Output Directories --
	location "%{wks.location}/Engine/"

	targetdir (target_dir)
	objdir    (object_dir)

	-- Compiler --
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	pchsource "src/Engine/ltpch.cpp"
	pchheader "ltpch.h"

	-- Project Files --
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
		"%{include_dirs.glad}",
		"%{include_dirs.glfw}",
		"%{include_dirs.glm}",
		"%{include_dirs.imgui}",
		"%{include_dirs.imgui_backends}",
		"%{include_dirs.spdlog}",
		"%{include_dirs.stb_image}",
		"%{include_dirs.volk}",
	}

	-- Links --
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"stb_image",
		"entt",
	}
	
	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LIGHT_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "on"

		links
		{
			"d3d11.lib",
			"dxguid.lib",
			"D3DCompiler.lib",
		}

		flags { "MultiProcessorCompile" }
	
	filter { "system:windows", "files:src/Platform/OS/Linux/**.**" }
		flags { "ExcludeFromBuild" }

	-- linux
	filter "system:linux"
		defines "LIGHT_PLATFORM_LINUX"
		links
		{
			"dl",
		}
		
		buildoptions
		{
			"-lgtest",
			"-lpthread",
		}
		
		filter { "system:linux", "files:src/Platform/GraphicsAPI/DirectX/**.**" }
			flags { "ExcludeFromBuild" }
		filter { "system:linux", "files:src/Platform/OS/Windows/**.**" }
			flags "ExcludeFromBuild"
		
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

	filter { "files:**.hlsl" }
		flags "ExcludeFromBuild"
		shadermodel "4.0"