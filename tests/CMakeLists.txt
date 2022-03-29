message("\n--> Building CrossPlatformSockets_tests\n")
project(CrossPlatformSockets_tests)

# Pull in GTest
# For more, see: https://github.com/google/googletest/blob/main/googletest/README.md
include(FetchContent)
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing and setup tests
enable_testing()

include_directories(${CROSS_PLATFORM_SOCKETS_INCLUDE_DIRS})

add_executable(CrossPlatformSockets_tests

   ${CMAKE_CURRENT_LIST_DIR}/Test_TcpStream.cpp
)

target_link_libraries(CrossPlatformSockets_tests gtest gtest_main)
target_link_libraries(CrossPlatformSockets_tests CrossPlatformSockets)

add_test(NAME CrossPlatformSockets_utests COMMAND CrossPlatformSockets_tests)