#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

// This include is required to initialize WSA, but also pulls in winsock2
#include "WinSockInitiator.hpp"

#include "ITcpListener.hpp"
#include <mutex>

namespace CrossPlatformSockets
{

class TcpListener : public ITcpListener
{
public:

   TcpListener() = default;
   TcpListener(int max_allowed_connections);
   TcpListener(const TcpListener&) = delete;
   TcpListener(TcpListener&&) = default;

   TcpListener& operator=(const TcpListener&) = delete;
   TcpListener& operator=(TcpListener&&) = default;

   std::optional<SocketAddress> get_address() const noexcept override;
   int get_max_allowed_connections() const noexcept override;

   // @TODO Static bind function that returns an optional<TcpListener>
   bool bind_to(const SocketAddress& socket_address) override;
   bool is_bound() const noexcept override;

private:

   const int m_max_allowed_connections = SOMAXCONN;

   mutable std::mutex m_mutex;

   // Guarded by m_mutex
   // This will be non-null once the listener is bound to an address
   std::optional<SocketAddress> m_address = std::nullopt;

   // Guarded by m_mutex
   SOCKET m_listener_socket = INVALID_SOCKET;

};

} // CrossPlatformSockets

#endif // TCP_LISTENER_HPP