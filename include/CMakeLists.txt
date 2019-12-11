project(fixed_point_dsp)

cmake_minimum_required(VERSION 3.13.0)

add_library(imfixedpoint INTERFACE)
target_sources(imfixedpoint INTERFACE
    include/imfixedpoint/number.hpp
)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR})

install(
    DIRECTORY include/imfixedpoint
    DESTINATION include
)