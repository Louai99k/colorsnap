# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.29)

# Define the project name
project(colorsnap)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add compiler optimization flags for the release build
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Add an executable target
add_executable(${PROJECT_NAME} src/colorsnap.cpp src/utils.cpp)

# Specify the C++ standard to use
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Include directories
include_directories(includes headers)
