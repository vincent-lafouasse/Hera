cmake_minimum_required(VERSION 3.16)

project(Hera VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(cmake/platform.cmake)

add_subdirectory(lib/juce)
add_subdirectory(Hera)
