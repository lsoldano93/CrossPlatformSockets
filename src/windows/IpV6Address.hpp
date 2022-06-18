#ifndef IPV6_ADDRESS_HPP
#define IPV6_ADDRESS_HPP

#include <optional>
#include <string>

namespace CrossPlatformSockets 
{

class IpV6Address
{
public:

   IpV6Address() = delete;
   virtual ~IpV6Address() = default;

   static std::optional<IpV6Address> create(std::string&& address_string) noexcept;

};

} // CrossPlatformSockets

#endif // IPV6_ADDRESS_HPP