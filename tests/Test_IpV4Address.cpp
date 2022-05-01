#include <gtest/gtest.h>

#include "IpV4Address.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
}

TEST(IpV4Address, FactoryFunctions) 
{
   auto address = IpV4Address::create("127.0.0.1");
   EXPECT_TRUE(address.has_value());
}

TEST(IpV4Address, Getters) 
{
   auto address = IpV4Address::create("127.0.0.1");
   EXPECT_EQ(LINK_LOCAL_ADDR, address->get_address());
   EXPECT_EQ("127.0.0.1", address->to_string());
}