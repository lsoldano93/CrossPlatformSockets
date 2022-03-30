
#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Construct a new Socket Address
* 
* @param[in] ipAddr is the ip address that will be assigned to this SocketAddress
* @param[in] port is the port that will be assigned to this SocketAddress
***************************************************************************************************/
SocketAddress::SocketAddress(const uint32_t ipAddr, const uint16_t port) :
   m_ip_addr(ipAddr),
   m_port(port)
{

}

/***********************************************************************************************//**
* @brief Return the ip address of this SocketAddress
* 
* @return The current ip address
***************************************************************************************************/
uint32_t SocketAddress::get_ip_addr() const
{
   return m_ip_addr;
}

/***********************************************************************************************//**
* @brief Return the port of this SocketAddress
* 
* @return The current port
***************************************************************************************************/
uint16_t SocketAddress::get_port() const
{
   return m_port;
}