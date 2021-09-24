cmake_minimum_required(VERSION 3.14)

project(Light VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(SPIRV_CROSS_ENABLE_TESTS OFF)
set(INSTALL_GTEST OFF)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
endif()
add_subdirectory(Dependencies/ShaderConductor) # <-- this project should not use "cxx_standard 17"

# directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MIRROR_DIR  ${CMAKE_BINARY_DIR}/../Mirror/)
set(ENGINE_DIR  ${CMAKE_BINARY_DIR}/../Engine/)
set(DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/../Dependencies/)

# projects
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_compile_definitions(LIGHT_PLATFORM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(LIGHT_PLATFORM_LINUX)
endif()

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
target_link_libraries(Engine ShaderConductor)

target_link_libraries(imgui glad)
target_link_libraries(imgui glfw)

target_link_libraries(Mirror Engine)

if(MSVC)
    set_property(DIRECTORY ${CMAE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Mirror)
endif()
