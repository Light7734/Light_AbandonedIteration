-- environment directories
vulkan_sdk_env_dir = os.getenv("VULKAN_SDK")

-- include directories
include_dirs = {}

include_dirs["entt"] = "%{wks.location}/Dependencies/entt/"
include_dirs["glad"] = "%{wks.location}/Dependencies/GLAD/include"
include_dirs["glfw"] = "%{wks.location}/Dependencies/GLFW/include"
include_dirs["glm"] = "%{wks.location}/Dependencies/glm"
include_dirs["imgui"] = "%{wks.location}/Dependencies/imgui"
include_dirs["imgui_backends"] = "%{wks.location}/Dependencies/imgui/backends"
include_dirs["spdlog"] = "%{wks.location}/Dependencies/spdlog/include"
include_dirs["stb_image"] = "%{wks.location}/Dependencies/stb_image"
include_dirs["volk"] = "%{wks.location}/Dependencies/volk"
include_dirs["shaderc"] = "%{wks.location}/Dependencies/shaderc/libshaderc/include"
include_dirs["glslang"] = "%{wks.location}/Dependencies/glslang/"
include_dirs["spirv"] = "%{wks.location}/Dependencies/spirv-headers/include"

include_dirs["engine"] = "%{wks.location}/Engine/src/Engine"
include_dirs["engine_platform_graphics"] = "%{wks.location}/Engine/src/Platform/GraphicsAPI"
include_dirs["engine_platform_os"] = "%{wks.location}/Engine/src/Platform/OS"

include_dirs["vulkan_sdk"] = "%{vulkan_sdk_env_dir}/Include"

-- library directories
lib_dirs = {}
lib_dirs["vulkan_sdk"] = "%{vulkan_sdk_env_dir}/Lib/"

-- libraries
libs = {}

libs["shaderc"] = "%{vulkan_sdk_env_dir}/Lib/shaderc_shared.lib"
libs["spirv_cross"] = "%{vulkan_sdk_env_dir}/Lib/spirv-cross-core.lib"
libs["spirv_tools"] = "%{vulkan_sdk_env_dir}/Lib/SPIRV-Tools.lib"