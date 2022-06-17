#ifndef WIN_SOCK_INITIATOR_H
#define WIN_SOCK_INITIATOR_H

#include "winsock2.h"
#include <stdexcept>
#include <string>

namespace CrossPlatformSockets
{
namespace Private // Do not use anything in this namespace directly
{
namespace Windows // Just to completely hammer home that this namespace is NOT cross platform
{

// Won't mark as do not use as WSA is reference counted, thus if someone accidentally uses this, 
// they will merely be reference counting on top of the static global below, however...
// @warning DO NOT USE THIS STRUCT AS IT IS UNNECESSARY AND NOT CROSS PLATFORM 
struct WinSockInitiator
{
   WinSockInitiator()
   {
      // Uses WinSock version 2.2
      WSAStartup(MAKEWORD(2, 2), &m_wsa_data);
   }

   ~WinSockInitiator()
   {
      WSACleanup();
   }

   WSADATA m_wsa_data;

};

// Create global to initialize WSA and on end of app, this will end
static const WinSockInitiator DO_NOT_USE_WIN_SOCK_INITIATOR;

} // Windows
} // Private
} // CrossPlatformSockets

#endif // WIN_SOCK_INITIATOR_H