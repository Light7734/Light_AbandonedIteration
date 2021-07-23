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
include "../Dependencies/GLFW/"
include "../Dependencies/GLAD/"
include "../Dependencies/imgui/"
