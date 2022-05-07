#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

#include "ITcpListener.hpp"

namespace CrossPlatformSockets
{

class TcpListener : public ITcpListener
{
public:

   TcpListener() = default;

   bool bind(const SocketAddress& socket_address) override;
   bool is_bound() const noexcept override;
   std::optional<SocketAddress> get_address() const noexcept override;

private:

   std::optional<SocketAddress> m_address = std::nullopt;

};

} // CrossPlatformSockets

#endif // TCP_LISTENER_HPP