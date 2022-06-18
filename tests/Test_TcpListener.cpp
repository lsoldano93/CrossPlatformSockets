#include <gtest/gtest.h>

#include "TcpListener.hpp"

using namespace CrossPlatformSockets;

namespace 
{
   constexpr uint32_t LINK_LOCAL_ADDR = 2130706433;
   constexpr uint16_t PORT = 8000;
}

TEST(TcpListener, Constructors) 
{
   TcpListener listener_default;
   TcpListener listener_with_max_connections(5);
   EXPECT_EQ(5, listener_with_max_connections.get_max_allowed_connections());
}

TEST(TcpListener, BindToIpV4Address) 
{
   // Make address
   auto socket_address = SocketAddress::createV4(LINK_LOCAL_ADDR, PORT);

   TcpListener tcp_listener;
   auto returned_socket_address_optional = tcp_listener.get_address();
   EXPECT_FALSE(returned_socket_address_optional.has_value());
   EXPECT_FALSE(tcp_listener.is_bound());

   EXPECT_TRUE(tcp_listener.bind_to(*socket_address));
   EXPECT_TRUE(tcp_listener.is_bound());

   returned_socket_address_optional = tcp_listener.get_address();
   ASSERT_TRUE(returned_socket_address_optional.has_value());
   //EXPECT_EQ(socket_address, *returned_socket_address_optional);
}

// TEST(TcpListener, AcceptIpV4Connection)
// {
//    // Make address
//    auto socket_address = SocketAddress::createV4(LINK_LOCAL_ADDR, PORT);

//    TcpListener tcp_listener;
//    ASSERT_TRUE(tcp_listener.bind_to(socket_address));

//    auto client_stream = tcp_listener.accept_connection();
//    EXPECT_TRUE(client_stream.has_value());
// }