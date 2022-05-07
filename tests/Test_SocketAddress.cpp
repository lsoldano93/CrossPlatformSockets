#include <gtest/gtest.h>

#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8000;
}

TEST(SocketAddress, IpV4SocketAddressConstruction) 
{
   auto ip_address = IpV4Address::create(LINK_LOCAL_ADDR);
   ASSERT_TRUE(ip_address.has_value());
   SocketAddress socket_address(std::move(*ip_address), PORT);

   auto ip_address_variant = socket_address.get_ip_address();
   auto ipv4_address_pointer = std::get_if<IpV4Address>(&ip_address_variant);
   ASSERT_NE(nullptr, ipv4_address_pointer);
   EXPECT_EQ(LINK_LOCAL_ADDR, ipv4_address_pointer->get_address());

   EXPECT_EQ(PORT, socket_address.get_port());
}