# Unit tests will require C++20
set(CMAKE_CXX_STANDARD 20)

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

enable_testing()

add_executable(
   CrossPlatformSockets_tests
   Test_TcpStream.cpp
)
target_link_libraries(
   CrossPlatformSockets_tests
   gtest_main
)
add_test(
   CrossPlatformSockets_tests CrossPlatformSockets_tests
)