#include <gtest/gtest.h>

#include "TcpListener.hpp"
#include "TcpStream.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8001;
}

// TEST(TcpStream, ConnectToIpV4Address) 
// {
//    // Make address
//    auto ip_address_optional = IpV4Address::create(LINK_LOCAL_ADDR);
//    ASSERT_TRUE(ip_address_optional.has_value());
//    auto socket_address = SocketAddress(std::move(*ip_address_optional), PORT);

//    TcpListener tcp_listener;
//    ASSERT_TRUE(tcp_listener.bind(socket_address));

//    TcpStream tcp_stream;
//    EXPECT_FALSE(tcp_stream.is_connected());
//    ASSERT_TRUE(tcp_stream.connect(socket_address));
//    EXPECT_TRUE(tcp_stream.is_connected());
// }