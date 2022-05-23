#include "IpV4Address.hpp"

#include "winsock2.h"
#include "Ws2tcpip.h"

#include <cstdio>

using namespace CrossPlatformSockets;

namespace
{
   constexpr size_t IP_ADDRESS_STRING_LENGTH = 16;
}

/***********************************************************************************************//**
* @brief Constructs an IpV4 address if the given address was a valid IpV4 representation in the 
*        format a.b.c.d - otherwise the returned optional will be null
*
* @param[in] address_string: string to use for address construction
*
* @return Returns a valid IpV4 address object on success; a null object if a valid IpV4 string was
*         not provided
***************************************************************************************************/
std::optional<IpV4Address> IpV4Address::create(std::string address_string) noexcept 
{
   const auto address = inet_addr(address_string.c_str());
   if (INADDR_NONE != address) 
   {
      return IpV4Address{ntohl(address), std::move(address_string)};
   }
      
   return std::nullopt;
}

/***********************************************************************************************//**
* @brief Constructs an IpV4 address if the given address was a valid IpV4 address IN HOST ORDER
*        This function WILL NOT work if a network order value is provided
*
* @param[in] host_address: host order address to use for address construction
*
* @return Returns a valid IpV4 address object on success; a null object if a valid IpV4 string was
*         not provided
***************************************************************************************************/
std::optional<IpV4Address> IpV4Address::create(const uint32_t host_address) noexcept
{
   char buffer[IP_ADDRESS_STRING_LENGTH];
   const uint32_t network_address = htonl(host_address);
   if (nullptr != inet_ntop(AF_INET, &network_address, buffer, IP_ADDRESS_STRING_LENGTH))
   {
      return IpV4Address(host_address, std::string(buffer));
   }
      
   return std::nullopt;
}

/***********************************************************************************************//**
* @brief Constructs an IpV4 address if the given address was a valid IpV4 representation in the 
*        format first_octet.second_octet.third_octet.fourt_octet - otherwise the returned optional 
*        will be null
* 
* @param[in] first_octet: The value a in the address a.b.c.d
* @param[in] second_octet: The value b in the address a.b.c.d
* @param[in] third_octet: The value c in the address a.b.c.d
* @param[in] fourth_octet: The value d in the address a.b.c.d
*
* @return Returns a valid IpV4 address object on success; a null object if values did not form a 
*         valid IpV4 address
***************************************************************************************************/
std::optional<IpV4Address> IpV4Address::create(const uint8_t first_octet, 
                                               const uint8_t second_octet, 
                                               const uint8_t third_octet, 
                                               const uint8_t fourth_octet) noexcept
{
   uint32_t host_address = first_octet;
   host_address = (host_address << 8) + second_octet;
   host_address = (host_address << 8) + third_octet;
   host_address = (host_address << 8) + fourth_octet;
   return IpV4Address::create(host_address);
}

/***********************************************************************************************//**
* @brief Construct a new IpV4 Address
* 
* @param[in] address: a host order representation of the address
* @param[in] address_string: string representation of the address
***************************************************************************************************/
IpV4Address::IpV4Address(const uint32_t address, std::string&& address_string) noexcept :
   m_address(std::move(address)),
   m_address_string(std::move(address_string))
{

}

/***********************************************************************************************//**
* @brief Returns the address value of this IpV4 in host order
*        (EG: "127.0.0.1" would be returnd as 2130706433)
* 
* @return Returns the address
***************************************************************************************************/
const uint32_t IpV4Address::get_address() const noexcept
{
   return m_address;
}

/***********************************************************************************************//**
* @brief Returns a string representation of this address (EG: "127.0.0.1")
* 
* @return Returns the string representation of this address
***************************************************************************************************/
const std::string& IpV4Address::to_string() const noexcept
{
   return m_address_string;
}