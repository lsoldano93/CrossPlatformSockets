cmake_minimum_required(VERSION 3.23)

# Name project
message("\n--> Building CrossPlatformSockets\n")
project(CrossPlatformSockets)

# Use C++20
message("--> Setting standard to C++20")
set(CMAKE_CXX_STANDARD 20)

# Option to build unit tests
option(BUILD_CROSS_PLATFORM_SOCKETS_UNIT_TESTS "Build CrossPlatformSockets unit tests" OFF)

# Add src dir
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

# Add unit tests if specified
if (BUILD_CROSS_PLATFORM_SOCKETS_UNIT_TESTS)
   add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
endif (BUILD_CROSS_PLATFORM_SOCKETS_UNIT_TESTS)