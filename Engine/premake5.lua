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
		"%{prj.location}/src/**.h"      ,
		"%{prj.location}/src/**.cpp"    ,
		"%{prj.location}/**.lua"        ,
		"%{prj.location}/dxgidebug.dll" ,
	}
	
	-- Dependencies --
	includedirs
	{
		-- engine
		"%{prj.location}/src/"                     ,
		"%{prj.location}/src/Engine/"              ,
		"%{prj.location}/src/Platform/GraphicsAPI" ,
		"%{prj.location}/src/Platform/OS"          ,

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "glfw/include/"  ),
		(dependenciesdir .. "glad/include"   ),
		(dependenciesdir .. "imgui/backends" ),
		(dependenciesdir .. "imgui/"         ),
		(dependenciesdir .. "glm/"           ),
	}

	links
	{
		"GLFW"  ,
		"GLAD"  ,
		"ImGui" ,
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

	--- Excludes ---
	-- !windows
	filter "system:not windows"
		excludes "%{prj.location}/src/Platform/GraphicsAPI/DirectX**"
		excludes "%{prj.location}/src/Platform/OS/Windows**"
	-- !linux #todo:
	-- !mac #todo: