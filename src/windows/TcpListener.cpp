#include "TcpListener.hpp"

using namespace CrossPlatformSockets;

/***********************************************************************************************//**
* @brief Binds this listener to the given socket address such that connections can be made to it
* 
* @param[in] socket_address: the address to bind this listener to
*
* @return Returns true if this listener bound to the given socket_address successfully; false o/w
***************************************************************************************************/
bool TcpListener::bind(const SocketAddress& socket_address)
{
   return true;
}

/***********************************************************************************************//**
* @brief Returns whether or not this listener is currently bound to a socket address
* 
* @return Returns true if it is bound; returns false o/w
***************************************************************************************************/
bool TcpListener::is_bound() const noexcept
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

}