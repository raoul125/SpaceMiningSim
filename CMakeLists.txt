# Choose a compatible CMake version
cmake_minimum_required(VERSION 3.10)

# Project Name
project(LunarMiningSim)

# Set the C++ standard to c++14
set(CMAKE_CXX_STANDARD 14)

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set Source Dir
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")

# Add all header files
file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.h")

# Add all source files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Enable Debug Symbols for Debug Builds
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add the source files to the project
add_executable(LunarMiningSim ${SOURCES} ${HEADERS})

# Set build types if not already set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release)" FORCE)
endif()
