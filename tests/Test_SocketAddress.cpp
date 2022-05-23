#include <gtest/gtest.h>

#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8000;
}

TEST(SocketAddress, ByV4AddressConstruction) 
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

TEST(SocketAddress, CreateV4AddressString) 
{
   auto socket_address = SocketAddress::createV4("127.0.0.1", PORT);
   ASSERT_TRUE(socket_address.has_value());
   EXPECT_EQ(PORT, socket_address->get_port());

   auto ip_address_variant = socket_address->get_ip_address();
   auto ipv4_address_pointer = std::get_if<IpV4Address>(&ip_address_variant);
   EXPECT_EQ(LINK_LOCAL_ADDR, ipv4_address_pointer->get_address());
   EXPECT_EQ("127.0.0.1", ipv4_address_pointer->to_string());
}

TEST(SocketAddress, CreateV4AddressHost) 
{
   auto socket_address = SocketAddress::createV4(LINK_LOCAL_ADDR, PORT);
   ASSERT_TRUE(socket_address.has_value());
   EXPECT_EQ(PORT, socket_address->get_port());

   auto ip_address_variant = socket_address->get_ip_address();
   auto ipv4_address_pointer = std::get_if<IpV4Address>(&ip_address_variant);
   EXPECT_EQ(LINK_LOCAL_ADDR, ipv4_address_pointer->get_address());
   EXPECT_EQ("127.0.0.1", ipv4_address_pointer->to_string());
}

TEST(SocketAddress, CreateV4AddressOctets) 
{
   auto socket_address = SocketAddress::createV4(127, 0, 0, 1, PORT);
   ASSERT_TRUE(socket_address.has_value());
   EXPECT_EQ(PORT, socket_address->get_port());

   auto ip_address_variant = socket_address->get_ip_address();
   auto ipv4_address_pointer = std::get_if<IpV4Address>(&ip_address_variant);
   EXPECT_EQ(LINK_LOCAL_ADDR, ipv4_address_pointer->get_address());
   EXPECT_EQ("127.0.0.1", ipv4_address_pointer->to_string());
}