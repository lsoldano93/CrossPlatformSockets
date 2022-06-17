#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

#include "ITcpListener.hpp"
#include <mutex>

namespace CrossPlatformSockets
{

class TcpListener : public ITcpListener
{
public:

   TcpListener() = default;
   TcpListener(const TcpListener&) = delete;
   TcpListener(TcpListener&&) = default;
   virtual ~TcpListener();

   TcpListener& operator=(const TcpListener&) = delete;
   TcpListener& operator=(TcpListener&&) = default;

   bool bind(const SocketAddress& socket_address) override;
   bool is_bound() const noexcept override;
   std::optional<SocketAddress> get_address() const noexcept override;

private:

   mutable std::mutex m_mutex;

   // Guarded by m_mutex
   // This will be non-null once the listener is bound to an address
   std::optional<SocketAddress> m_address = std::nullopt;

   // Guarded by m_mutex
   class SOCKET;
   SOCKET* m_listener_socket;

};

} // CrossPlatformSockets

#endif // TCP_LISTENER_HPP