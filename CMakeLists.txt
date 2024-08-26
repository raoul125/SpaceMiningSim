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

# Add the source files to the project
add_executable(LunarMiningSim ${SOURCES} ${HEADERS})
