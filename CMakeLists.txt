cmake_minimum_required(VERSION 3.21.2)

project(Light VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
# target_compile_features(Light PUBLIC cxx_std_17)
# set_property(TARGET Light CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SANDBOX_DIR ${CMAKE_BINARY_DIR}/../Sandbox/)
set(MIRROR_DIR  ${CMAKE_BINARY_DIR}/../Mirror/)
set(ENGINE_DIR  ${CMAKE_BINARY_DIR}/../Engine/)
set(DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/../Dependencies/)

# SANDBOX
file(GLOB SANDBOX_SRC ABSOLUTE ${SANDBOX_DIR}/src/*.*)
file(GLOB SANDBOX_RES_TEXTURES ABSOLUTE ${SANDBOX_DIR}/res/Textures/*.*)
source_group(src/         FILES ${SANDBOX_SRC})
source_group(res/Textures FILES ${SANDBOX_RES_TEXTURES})

add_executable(Sandbox ${SANDBOX_SRC} ${SANDBOX_RES_TEXTURES})

# MIRROR
add_compile_definitions(LIGHT_PLATFORM_WINDOWS)

# projects
add_subdirectory(${ENGINE_DIR}/)
add_subdirectory(${MIRROR_DIR}/)

add_subdirectory(${DEPENDENCIES_DIR}GLAD/)
add_subdirectory(${DEPENDENCIES_DIR}GLFW/)
add_subdirectory(${DEPENDENCIES_DIR}spdlog/)
add_subdirectory(${DEPENDENCIES_DIR}glm/)
add_subdirectory(${DEPENDENCIES_DIR}entt/)
add_subdirectory(${DEPENDENCIES_DIR}imgui/)
add_subdirectory(${DEPENDENCIES_DIR}stb_image/)

target_link_libraries(Engine glad)
target_link_libraries(Engine glfw)
target_link_libraries(Engine spdlog)
target_link_libraries(Engine imgui)
target_link_libraries(Engine stb_image)

target_link_libraries(imgui glad)
target_link_libraries(imgui glfw)

target_link_libraries(Mirror Engine)