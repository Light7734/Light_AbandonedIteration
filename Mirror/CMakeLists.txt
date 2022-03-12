cmake_minimum_required(VERSION 3.14)

add_compile_definitions(LIGHT_PLATFORM_WINDOWS)

include_directories(
    ${ENGINE_DIR}src/Engine/
    ${MIRROR_DIR}/src/
    ${ENGINE_DIR}src/Platform/GraphicsAPI/
    ${ENGINE_DIR}src/Platform/OS/
    ${DEPENDENCIES_DIR}entt/src/
    ${DEPENDENCIES_DIR}GLAD/include/
    ${DEPENDENCIES_DIR}GLFW/include/
    ${DEPENDENCIES_DIR}glm/
    ${DEPENDENCIES_DIR}imgui/
    ${DEPENDENCIES_DIR}spdlog/include
    ${DEPENDENCIES_DIR}stb_image/
    ${DEPENDENCIES_DIR}yaml-cpp/include
)


file(GLOB_RECURSE MIRROR_FILES true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/src/* ${CMAKE_CURRENT_SOURCE_DIR}/res/*)
source_group(TREE ${MIRROR_DIR} FILES ${MIRROR_FILES})
add_executable(Mirror ${MIRROR_FILES})
