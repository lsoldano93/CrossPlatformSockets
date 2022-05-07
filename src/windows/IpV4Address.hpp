#ifndef IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <iostream>

namespace CrossPlatformSockets 
{

class IpV4Address
{
public:

   IpV4Address() = delete;

   static std::optional<IpV4Address> create(std::string&& address_string) noexcept;
   static std::optional<IpV4Address> create(const uint32_t host_address) noexcept;
   static std::optional<IpV4Address> create(const uint8_t first_octet, 
                                            const uint8_t second_octet, 
                                            const uint8_t third_octet, 
                                            const uint8_t fourth_octet) noexcept;

   const uint32_t get_address() const noexcept;
   const std::string& to_string() const noexcept;

   friend std::ostream& operator<<(std::ostream& os, const IpV4Address& address)
   {
      os << address.to_string();
      return os;
   }

private:

   IpV4Address(const uint32_t address, std::string&& address_string) noexcept;

   const uint32_t m_address;
   const std::string m_address_string;

};

} // CrossPlatformSockets

#endif // IPV4_ADDRESS_HPP