#ifndef _NETWORK_H_
#define _NETWORK_H_

#ifdef _WIN32

#include <winsock2.h>
#include <windows.h>

namespace Network
{
	inline bool Init()
	{
		WSADATA wsaData;
		if( 0 != WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) )
			return false;
		return true;
	}

	inline void Cleanup()
	{
		WSACleanup();
	}
}

#else

namespace Network
{
	inline bool Init()
	{
		return true;
	}

	inline void Cleanup()
	{
	}
}

#endif

#endif // _NETWORK_H_
