#ifndef I_TCP_LISTENER_H
#define I_TCP_LISTENER_H

#include "SocketAddress.hpp"

#include <optional>

namespace CrossPlatformSockets 
{

class ITcpListener
{
public:

   virtual bool bind(const SocketAddress& socket_address) = 0;
   virtual bool is_bound() const noexcept = 0;
   virtual std::optional<SocketAddress> get_address() const noexcept = 0;

protected:

   virtual ~ITcpListener() = default;

};

} // namespace CrossPlatformSockets

#endif // I_TCP_LISTENER_H