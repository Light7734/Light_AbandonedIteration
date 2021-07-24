project "Engine"

	-- Output Directories --
	location "%{wks.location}/Engine/"

	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	-- kind
	kind "StaticLib"

	-- language
	language "C++"
	cppdialect "C++17"

	-- pch
	pchsource "src/Engine/ltpch.cpp"
	pchheader "ltpch.h"

	-- Project Files ---
	files
	{
		-- src
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		
		-- premake
		"%{prj.location}/build.lua",
		
		"%{prj.location}/res/**"
	}
	
	-- Dependencies --
	includedirs
	{
		-- engine
		"%{prj.location}"                          ,
		"%{prj.location}/src"                      ,
		"%{prj.location}/src/Engine"               ,
		"%{prj.location}/src/Platform/GraphicsAPI" ,
		"%{prj.location}/src/Platform/OS"          ,

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "GLFW/include/"),
		(dependenciesdir .. "GLAD/include"),
		(dependenciesdir .. "imgui/backends"),
		(dependenciesdir .. "imgui/"),
		(dependenciesdir .. "stb_image/"),
		(dependenciesdir .. "glm/"),
		(dependenciesdir .. "entt/"),
	}

	links
	{
		"GLFW"  ,
		"GLAD"  ,
		"ImGui" ,
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
			"d3d11.lib"       ,
			"dxguid.lib"      ,
			"D3DCompiler.lib" ,
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
		optimize "on"

	filter { "files:**.hlsl" }
		flags "ExcludeFromBuild"
		shadermodel "4.0"