#include "IpV4Address.hpp"

#include "winsock2.h"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Constructs an IpV4 address if the given address was a valid IpV4 representation in the 
*        format a.b.c.d - otherwise the returned optional will be null
*
* @param[in] address_string: string to use for address construction
*
* @return Returns a valid IpV4 address object on success; a null object if a valid IpV4 string was
*         not provided
***************************************************************************************************/
std::optional<IpV4Address> IpV4Address::create(std::string&& address_string) noexcept 
{
   auto address = inet_addr(address_string.c_str());
   if (INADDR_NONE != address) 
   {
      return IpV4Address{ntohl(address), std::move(address_string)};
   }
   else 
   {
      return std::nullopt;
   }
}

/***********************************************************************************************//**
* @brief Construct a new IpV4 Address
* 
* @param[in] address: a hardware order representation of the address
* @param[in] address_string: string representation of the address
***************************************************************************************************/
IpV4Address::IpV4Address(uint32_t&& address, std::string&& address_string) noexcept :
   m_address(std::move(address)),
   m_address_string(std::move(address_string))
{

}

/***********************************************************************************************//**
* @brief Returns the address value of this IpV4 in hardware order
*        (EG: "127.0.0.1" would be returnd as 2130706433)
* 
* @return Returns the address
***************************************************************************************************/
const uint32_t& IpV4Address::get_address() const noexcept
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