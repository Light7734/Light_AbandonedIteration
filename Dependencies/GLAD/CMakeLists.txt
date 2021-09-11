cmake_minimum_required(VERSION 3.21.2)

if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-w)
endif()
if(MSVC)
    add_compile_options(/MP)
    add_compile_options(/W0)
endif()

project(GLAD VERSION 0.1.34 LANGUAGES C)

file(GLOB_RECURSE GLAD_SOURCES true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE GLAD_HEADERS true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})