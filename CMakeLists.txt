cmake_minimum_required(VERSION 3.16)

project(Hera VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include(cmake/cpm.cmake)
include(cmake/platform.cmake)

CPMAddPackage(
    NAME JUCE
    GIT_TAG 8.0.2
    VERSION 8.0.2
    GITHUB_REPOSITORY juce-framework/JUCE
    SOURCE_DIR ${LIB_DIR}/juce
)

add_subdirectory(Hera)
