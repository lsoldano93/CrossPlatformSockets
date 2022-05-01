#include <gtest/gtest.h>

#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8000;
}

TEST(SocketAddress, ConstructionAndGetters) 
{
   SocketAddress address(LINK_LOCAL_ADDR, PORT);
   EXPECT_EQ(address.get_ip_addr(), LINK_LOCAL_ADDR);
   EXPECT_EQ(address.get_port(), PORT);
}