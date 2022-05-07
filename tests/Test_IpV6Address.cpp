#include <gtest/gtest.h>

#include "IpV6Address.hpp"

using namespace CrossPlatformSockets;

TEST(IpV6Address, ByStringConstruction_Invalid) 
{
   auto address = IpV6Address::create("");
   ASSERT_FALSE(address.has_value());
}

