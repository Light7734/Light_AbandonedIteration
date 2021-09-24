cmake_minimum_required(VERSION 3.14)

if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-w)
endif()
if(MSVC)
    add_compile_options(/MP)
    add_compile_options(/W0)
endif()

add_compile_definitions(LIGHT_PLATFORM_WINDOWS)

include_directories(
${ENGINE_DIR}src/Engine/
${ENGINE_DIR}src/Platform/GraphicsAPI/
${ENGINE_DIR}src/Platform/OS/
${DEPENDENCIES_DIR}entt/src/
${DEPENDENCIES_DIR}GLAD/include/
${DEPENDENCIES_DIR}GLFW/include/
${DEPENDENCIES_DIR}glm/
${DEPENDENCIES_DIR}imgui/
${DEPENDENCIES_DIR}spdlog/include
${DEPENDENCIES_DIR}stb_image/
)


file(GLOB_RECURSE MIRROR_FILES true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/src/* ${CMAKE_CURRENT_SOURCE_DIR}/res/*)
source_group(TREE ${MIRROR_DIR} FILES ${MIRROR_FILES})
add_executable(Mirror ${MIRROR_FILES})
