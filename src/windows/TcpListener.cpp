#include "TcpListener.hpp"

// This include is required to initialize WSA, but also pulls in winsock2
#include "WinSockInitiator.hpp"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Custom destructor for TcpListener that ensures any allocated memory is freed, particularly
*        the memory associated with the listener socket 
***************************************************************************************************/
TcpListener::~TcpListener()
{
   if (nullptr != m_listener_socket)
   {
      delete m_listener_socket;
   }
}

/***********************************************************************************************//**
* @brief Binds this listener to the given socket address such that connections can be made to it
* 
* @param[in] socket_address: the address to bind this listener to
*
* @return Returns true if this listener bound to the given socket_address successfully; false o/w
***************************************************************************************************/
bool TcpListener::bind(const SocketAddress& socket_address)
{
   std::lock_guard<std::mutex> guard(m_mutex);
   if (nullptr != m_listener_socket)
   {
      return false;
   }

   auto ip_address_variant = socket_address.get_ip_address();
   if (nullptr != std::get_if<IpV4Address>(&ip_address_variant))
   {
      auto ipv4_address = std::get_if<IpV4Address>(&socket_address.get_ip_address());

      struct addrinfo* result = nullptr;
      struct addrinfo* ptr = nullptr;
      struct addrinfo hints;

      ZeroMemory(&hints, sizeof(hints)); // Fills memory with zeroes
      hints.ai_family = AF_INET; // IPV4
      hints.ai_socktype = SOCK_STREAM; // Stream socket
      hints.ai_protocol = IPPROTO_TCP; // TCP socket
      hints.ai_flags = AI_PASSIVE; // Outcome of getaddrinfo will be used in bind

      if (0 != getaddrinfo(ipv4_address->to_string().c_str(), 
                           socket_address.get_port(), 
                           &hints, 
                           &result))
      {
         return false;
      }

      m_listener_socket = new SOCKET;
      *m_listener_socket = INVALID_SOCKET;
      *m_listener_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
      if (INVALID_SOCKET == *m_listener_socket)
      {
         freeaddrinfo(result);
         delete m_listener_socket;
         return false;
      }

      if (SOCKET_ERROR == bind(*m_listener_socket, result->ai_addr, (int)result->ai_addrlen))
      {
         freeaddrinfo(result);
         closesocket(*m_listener_socket);
         delete m_listener_socket;
         return false;
      }

      // Cleanup result allocated by getaddrinfo
      freeaddrinfo(result);

      m_address = socket_address;
   }
   else if (nullptr != std::get_if<IpV6Address>(&socket_address.get_ip_address()))
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

/***********************************************************************************************//**
* @brief Gets the socket address this listener is bound to, if it is bound to an address
* 
* @return Returns an optional with a non null address if this listener is bound to an address;
*         returns a null optional if it is not currently bound to anything
***************************************************************************************************/
std::optional<SocketAddress> TcpListener::get_address() const noexcept
{
   std::lock_guard<std::mutex> guard(m_mutex);
   return std::nullopt;
}