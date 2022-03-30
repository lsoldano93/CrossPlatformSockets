#ifndef SOCKET_ADDRESS_HPP
#define SOCKET_ADDRESS_HPP

#include <cstdint>

namespace CrossPlatformSockets {

class SocketAddress
{
public:

   SocketAddress(const uint32_t ipAddr, const uint16_t port);

   uint32_t get_ip_addr() const;
   uint16_t get_port() const;

private:

   const uint32_t m_ip_addr;
   const uint16_t m_port;

};

} // CrossPlatformSockets

#endif // SOCKET_ADDRESS_HPP