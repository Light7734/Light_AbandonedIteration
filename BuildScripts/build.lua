workspace "Light"
	location "../"
	startproject "Mirror"

	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution",
	}

-- Directories --
dependenciesdir = "%{wks.location}/Dependencies/"
outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/%{prj.name}"

-- Projects --
include "../Engine/build.lua"
include "../Mirror/build.lua"
include "../Sandbox/build.lua"

-- Dependencies --
group "Dependencies"
include "../Dependencies/GLFW/build.lua"
include "../Dependencies/GLAD/build.lua"
include "../Dependencies/imgui/build.lua"
include "../Dependencies/stb_image/build.lua"
include "../Dependencies/entt/build.lua"
