
#include "SocketAddress.hpp"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Constructs an IpV4 socket address if the given address was a valid IpV4 representation in  
*        the format a.b.c.d - otherwise the returned optional will be null
* 
* @param[in] address_string: string to use for ip address construction
* @param[in] port: port to assign to socket address
*
* @return Returns a valid socket address representation of an IpV4 address on success; a null object
*         if a valid IpV4 string was not provided
***************************************************************************************************/
std::optional<SocketAddress> SocketAddress::createV4(std::string address_string,
                                                     const uint16_t port) noexcept
{
   auto ip_address = IpV4Address::create(std::move(address_string));
   if (ip_address.has_value())
   {
      return SocketAddress(std::move(*ip_address), port);
   }

   return std::nullopt;
}

/***********************************************************************************************//**
* @brief Constructs an IpV4 socket address if the given address was a valid address IN HOST ORDER 
*        This function WILL NOT work if a network order value is provided
*
* @param[in] host_address: host order address to use for address construction
* @param[in] port: port to assign to socket address
*
* @return Returns a valid socket address object on success; a null object if a valid IpV4 host order
*         address was not provided
***************************************************************************************************/
std::optional<SocketAddress> SocketAddress::createV4(const uint32_t host_address,
                                                     const uint16_t port) noexcept
{
   auto ip_address = IpV4Address::create(host_address);
   if (ip_address.has_value())
   {
      return SocketAddress(std::move(*ip_address), port);
   }

   return std::nullopt;
}

/***********************************************************************************************//**
* @brief Constructs an IpV4 socket address if the given address was a valid IpV4 representation in  
*        the format first_octet.second_octet.third_octet.fourt_octet - otherwise the returned  
*        optional will be null
* 
* @param[in] first_octet: The value a in the address a.b.c.d
* @param[in] second_octet: The value b in the address a.b.c.d
* @param[in] third_octet: The value c in the address a.b.c.d
* @param[in] fourth_octet: The value d in the address a.b.c.d
* @param[in] port: port to assign to socket address
*
* @return Returns a valid socket address object on success; a null object if values did not form a 
*         valid IpV4 address
***************************************************************************************************/
std::optional<SocketAddress> SocketAddress::createV4(const uint8_t first_octet, 
                                                     const uint8_t second_octet, 
                                                     const uint8_t third_octet, 
                                                     const uint8_t fourth_octet,
                                                     const uint16_t port) noexcept
{
   auto ip_address = IpV4Address::create(first_octet, second_octet, third_octet, fourth_octet);
   if (ip_address.has_value())
   {
      return SocketAddress(std::move(*ip_address), port);
   }

   return std::nullopt;
}

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
uint16_t SocketAddress::get_port() const noexcept
{
   return m_port;
}