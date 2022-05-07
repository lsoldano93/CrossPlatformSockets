message("\n--> Building CrossPlatformSockets_tests\n")
project(CrossPlatformSockets_tests)
set(CROSS_PLATFORM_SOCKETS_TESTS_TARGET_NAME "CrossPlatformSockets_tests")

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

add_executable(${CROSS_PLATFORM_SOCKETS_TESTS_TARGET_NAME}

               ${CROSS_PLATFORM_SOCKETS_SOURCE_FILES}
               ${CROSS_PLATFORM_SOCKETS_HEADER_FILES}

               ${CMAKE_CURRENT_LIST_DIR}/Test_IpV4Address.cpp
               ${CMAKE_CURRENT_LIST_DIR}/Test_IpV6Address.cpp
               ${CMAKE_CURRENT_LIST_DIR}/Test_SocketAddress.cpp
               ${CMAKE_CURRENT_LIST_DIR}/Test_TcpListener.cpp
               ${CMAKE_CURRENT_LIST_DIR}/Test_TcpStream.cpp
)

target_link_libraries(${CROSS_PLATFORM_SOCKETS_TESTS_TARGET_NAME} 
                      ${CROSS_PLATFORM_SOCKETS_LIBS}
                      gtest 
                      gtest_main)

target_include_directories(${CROSS_PLATFORM_SOCKETS_TESTS_TARGET_NAME} 
                           PRIVATE ${CROSS_PLATFORM_SOCKETS_INCLUDE_DIRS})

add_test(NAME CrossPlatformSockets_utests 
         COMMAND ${CROSS_PLATFORM_SOCKETS_TESTS_TARGET_NAME})