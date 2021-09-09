cmake_minimum_required(VERSION 3.21.2)

if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-w)
endif()
if(MSVC)
    add_compile_options(/MP)
    add_compile_options(/W0)
endif()

file(GLOB STB_IMAGES_FILES true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(stb_image STATIC ${STB_IMAGES_FILES})