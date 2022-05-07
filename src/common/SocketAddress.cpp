
#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Gets the ip address variant associated with this socket address
* 
* @return Returns ip address variant
***************************************************************************************************/
std::variant<IpV4Address, IpV6Address> SocketAddress::get_ip_address() const noexcept
{
   return m_ip_address;
}

/***********************************************************************************************//**
* @brief Gets the port associated with this socket address
* 
* @return Returns the port
***************************************************************************************************/
int16_t SocketAddress::get_port() const noexcept
{
   return m_port;
}