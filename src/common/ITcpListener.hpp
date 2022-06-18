#ifndef I_TCP_LISTENER_H
#define I_TCP_LISTENER_H

#include "ITcpStream.hpp"

#include <optional>

namespace CrossPlatformSockets 
{

class ITcpListener
{
public:

   virtual std::optional<SocketAddress> get_address() const noexcept = 0;
   virtual int get_max_allowed_connections() const noexcept = 0;

   virtual bool bind_to(const SocketAddress& socket_address) = 0;
   virtual bool is_bound() const noexcept = 0;

   // virtual std::optional<ITcpStream> accept_connection() = 0; 

protected:

   virtual ~ITcpListener() = default;

};

} // namespace CrossPlatformSockets

#endif // I_TCP_LISTENER_H