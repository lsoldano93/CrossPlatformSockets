#include <gtest/gtest.h>

#include "TcpListener.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8000;
}

TEST(TcpListener, BindToIpV4Address) 
{
   // Make address
   auto ip_address_optional = IpV4Address::create(LINK_LOCAL_ADDR);
   ASSERT_TRUE(ip_address_optional.has_value());
   auto socket_address = SocketAddress(std::move(*ip_address_optional), PORT);

   TcpListener tcp_listener;
   EXPECT_FALSE(tcp_listener.is_bound());
   EXPECT_TRUE(tcp_listener.bind(socket_address));
   EXPECT_TRUE(tcp_listener.is_bound());
}