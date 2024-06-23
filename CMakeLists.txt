# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.29)

# Define the project name
project(colorsnap)

# Set C++ Standarts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add an executable target
add_executable(${PROJECT_NAME} src/colorsnap.cpp src/utils.cpp)

# Include directories
include_directories(include lib)

# Install the executable
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin/)
endif()
