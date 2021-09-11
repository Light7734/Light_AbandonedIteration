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
<<<<<<< HEAD
include "../Dependencies/GLFW/build.lua"
include "../Dependencies/GLAD/build.lua"
include "../Dependencies/imgui/build.lua"
include "../Dependencies/stb_image/build.lua"
include "../Dependencies/entt/build.lua"
include "../Dependencies/volk/build.lua"
=======
	include "../Dependencies/GLFW/build.lua"
	include "../Dependencies/GLAD/build.lua"
	include "../Dependencies/imgui/build.lua"
	include "../Dependencies/stb_image/build.lua"
	include "../Dependencies/entt/build.lua"
	include "../Dependencies/shaderc/build.lua"
	include "../Dependencies/glslang/build.lua"
>>>>>>> 32341d184cb341d5af951d133b4a46d4f89c692e
