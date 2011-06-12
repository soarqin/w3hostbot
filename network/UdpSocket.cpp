#include "config.h"
#include "UdpSocket.h"

namespace Network
{
	class UdpWorkerThread:
		public Common::Thread
	{
	public:
		virtual uint Proc(void * param)
		{
			UdpSocket * us = (UdpSocket *)param;
			return us->Worker();
		}
	};

	UdpSocket::UdpSocket()
	{
		_shutdownEvent = NULL;
	}

	UdpSocket::~UdpSocket()
	{
		Destroy();
	}

	bool UdpSocket::Init( ushort port )
	{
		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(_socket == -1)
			return false;
		BOOL bOptVal = TRUE;
		setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOptVal, sizeof(BOOL));
		u_long iMode = 0;
		ioctlsocket(_socket, FIONBIO, &iMode);
		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = ::htons(port);
		if(bind(_socket, (const sockaddr *)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			Destroy();
			return false;
		}
		_shutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		_worker = Common::Thread::Pointer(new UdpWorkerThread());
		_worker->Start((void *)this);
		return true;
	}

	void UdpSocket::Destroy()
	{
		if(_shutdownEvent != NULL)
			SetEvent(_shutdownEvent);

		// Let Worker thread go down
		if(_worker.get() != 0)
		{
			if(_worker->GetId() > 0)
				_worker->Wait();
			_worker.reset();
		}
		if(_socket != 0)
		{
			closesocket(_socket);
			_socket = 0;
		}
		if(_shutdownEvent != NULL)
		{
			CloseHandle(_shutdownEvent);
			_shutdownEvent = NULL;
		}
	}

	void UdpSocket::Broadcast( ushort port, const byte * buf, size_t len )
	{
		Send(INADDR_BROADCAST, port, buf, len);
	}

	void UdpSocket::Send( uint ip, ushort port, const byte * buf, size_t len )
	{
		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = ::htons(port);
		addr.sin_addr.s_addr = ::htonl(ip);
		sendto(_socket, (const char *)buf, len, 0, (const sockaddr *)&addr, sizeof(sockaddr_in));
	}

	uint UdpSocket::Worker()
	{
		while(WAIT_OBJECT_0 != WaitForSingleObject(_shutdownEvent, 0))
		{
			byte buf[2048];
			sockaddr_in addr = {0};
			int addrlen = sizeof(sockaddr_in);
			int len = recvfrom(_socket, (char *)buf, 2048, 0, (sockaddr *)&addr, &addrlen);
			if(len < 0)
			{
				int err = WSAGetLastError();
				if (err != WSAEINTR && err != WSAEWOULDBLOCK && err != WSATRY_AGAIN && err != WSAECONNRESET && err != WSAENETRESET)
				{
					break;
				}
			}
			if(len > 0)
			{
				OnRecv(ntohl(addr.sin_addr.s_addr), ntohs(addr.sin_port), buf, len);
			}
		}
		return 0;
	}
}
