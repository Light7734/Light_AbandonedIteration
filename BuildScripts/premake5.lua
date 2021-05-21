workspace "Light"
	location "../"
	startproject "Sandbox"

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
include "../Sandbox/"
include "../Engine/"

group "Dependencies"
include "../Dependencies/GLFW/"