#ifndef IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <cstdint>
#include <optional>
#include <string>

namespace CrossPlatformSockets 
{

class IpV4Address
{
public:

   static std::optional<IpV4Address> create(std::string&& address_string) noexcept;

   const uint32_t& get_address() const noexcept;
   const std::string& to_string() const noexcept;

private:

   IpV4Address(uint32_t&& address, std::string&& address_string) noexcept;

   const uint32_t m_address;
   const std::string m_address_string;

};

} // CrossPlatformSockets

#endif // IPV4_ADDRESS_HPP