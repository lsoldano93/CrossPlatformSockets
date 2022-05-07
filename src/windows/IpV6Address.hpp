#ifndef IPV6_ADDRESS_HPP
#define IPV6_ADDRESS_HPP

#include <optional>
#include <string>

namespace CrossPlatformSockets 
{

class IpV6Address
{
public:

   static std::optional<IpV6Address> create(std::string&& address_string) noexcept;

private:

   IpV6Address() = default;

};

} // CrossPlatformSockets

#endif // IPV6_ADDRESS_HPP