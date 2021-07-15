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
include "../Engine/"
include "../Mirror/"
include "../Sandbox/"

-- Dependencies --
group "Dependencies"
include "../Dependencies/GLFW/"
include "../Dependencies/GLAD/"
include "../Dependencies/imgui/"
