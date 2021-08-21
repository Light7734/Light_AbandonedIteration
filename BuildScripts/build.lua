include "dependencies.lua"

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
target_dir = "%{wks.location}/bin/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/%{prj.name}"
object_dir = "%{wks.location}/bin-obj/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/%{prj.name}"

-- Projects --
group ""
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