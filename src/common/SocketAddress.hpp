#ifndef SOCKET_ADDRESS_HPP
#define SOCKET_ADDRESS_HPP

#include "IpV4Address.hpp"
#include "IpV6Address.hpp"

#include <concepts>
#include <cstdint>
#include <variant>

namespace CrossPlatformSockets 
{

template <typename T>
concept IsIpAddress = std::is_base_of<IpV4Address, std::remove_cvref_t<T>>::value || 
                      std::is_base_of<IpV6Address, std::remove_cvref_t<T>>::value;

class SocketAddress
{
public:

   SocketAddress() = delete;

   template <typename T> requires IsIpAddress<T>
   SocketAddress(T&& ip_address, const uint16_t port) noexcept;

   std::variant<IpV4Address, IpV6Address> get_ip_address() const noexcept;
   int16_t get_port() const noexcept;

private:

   std::variant<IpV4Address, IpV6Address> m_ip_address;
   int16_t m_port;

};

/***********************************************************************************************//**
* @brief Construct a new Socket Address
* 
* @tparam T should be a class that is a base of IpV4Address or IpV6Address
* @param[in] ip_address: the ip address (V4 or V6) associated with this socket address
* @param[in] port: the port associated with this socket address
***************************************************************************************************/
template <typename T> requires IsIpAddress<T>
SocketAddress::SocketAddress(T&& ip_address, const uint16_t port) noexcept :
   m_ip_address(std::forward<T>(ip_address)),
   m_port(port)   
{

}

} // CrossPlatformSockets

#endif // SOCKET_ADDRESS_HPP