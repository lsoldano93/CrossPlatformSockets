#include <gtest/gtest.h>

#include "ITcpStream.hpp"

// Demonstrate some basic assertions.
TEST(TcpStream, BasicAssertions) {
   std::cout << "this works" << std::endl;
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}