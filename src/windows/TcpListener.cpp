#include "TcpListener.hpp"

#include <assert.h>

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Constructs a TcpListener with a specified number of allowed maximum connections, whereas
*        the default empty constructor will set this to the max allowable/reasonable value by the 
*        system
*        https://www.ibm.com/docs/en/zos/2.4.0?topic=statements-somaxconn-statement
* 
* @param[in] max_allowed_connections: the max number of connections this listener can have running
*            with client streams at any moment
***************************************************************************************************/
TcpListener::TcpListener(int max_allowed_connections) :
   m_max_allowed_connections(max_allowed_connections)
{

}

/***********************************************************************************************//**
* @brief Gets the socket address this listener is bound to, if it is bound to an address
* 
* @return Returns an optional with a non null address if this listener is bound to an address;
*         returns a null optional if it is not currently bound to anything
***************************************************************************************************/
std::optional<SocketAddress> TcpListener::get_address() const noexcept
{
   std::lock_guard<std::mutex> guard(m_mutex);
   return m_address;
}

/***********************************************************************************************//**
* @brief Gets the maximum number of connections to this listener that are allowed
* 
* @return Returns max num connections allowed
***************************************************************************************************/
int TcpListener::get_max_allowed_connections() const noexcept
{
   return m_max_allowed_connections;
}

/***********************************************************************************************//**
* @brief Binds this listener to the given socket address such that connections can be made to it
* 
* @param[in] socket_address: the address to bind this listener to
*
* @return Returns true if this listener bound to the given socket_address successfully; false o/w
***************************************************************************************************/
bool TcpListener::bind_to(const SocketAddress& socket_address)
{
   std::lock_guard<std::mutex> guard(m_mutex);
   if (std::nullopt != m_address)
   {
      return false;
   }

   auto ip_address_variant = socket_address.get_ip_address();
   if (auto ipv4_address = std::get_if<IpV4Address>(&ip_address_variant))
   {
      struct addrinfo* result = nullptr;
      struct addrinfo* ptr = nullptr;
      struct addrinfo hints;

      ZeroMemory(&hints, sizeof(hints)); // Fills memory with zeroes
      hints.ai_family = AF_INET; // IPV4
      hints.ai_socktype = SOCK_STREAM; // Stream socket
      hints.ai_protocol = IPPROTO_TCP; // TCP socket
      hints.ai_flags = AI_PASSIVE; // Outcome of getaddrinfo will be used in bind

      if (0 != getaddrinfo(ipv4_address->to_string().c_str(), 
                           std::to_string(socket_address.get_port()).c_str(), 
                           &hints, 
                           &result))
      {
         return false;
      }

      m_listener_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
      if (INVALID_SOCKET == m_listener_socket)
      {
         freeaddrinfo(result);
         return false;
      }

      if (SOCKET_ERROR == bind(m_listener_socket, result->ai_addr, (int)result->ai_addrlen))
      {
         freeaddrinfo(result);
         closesocket(m_listener_socket);
         return false;
      }

      freeaddrinfo(result);

      m_address = socket_address;
   }
   else if (auto ipv6_address = std::get_if<IpV6Address>(&ip_address_variant))
   {
      // Not currently implemented
      assert(false);
      return false;
   }

   return true;
}

/***********************************************************************************************//**
* @brief Returns whether or not this listener is currently bound to a socket address
* 
* @return Returns true if it is bound; returns false o/w
***************************************************************************************************/
bool TcpListener::is_bound() const noexcept
{
   std::lock_guard<std::mutex> guard(m_mutex);
   return std::nullopt != m_address;
}