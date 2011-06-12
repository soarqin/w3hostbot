#ifndef _UDPSOCKET_H_
#define _UDPSOCKET_H_

#include "common/Thread.h"
#include "common/SharedPtr.h"

namespace Network
{
	class UdpSocket:
		public Common::SharedClass<UdpSocket>
	{
		friend class UdpWorkerThread;
	public:
		UdpSocket();
		~UdpSocket();
		bool Init(ushort port);
		void Destroy();
		void Broadcast(ushort port, const byte * buf, size_t len);
		void Send(uint ip, ushort port, const byte * buf, size_t len);
		virtual void Broadcast(ushort port, ushort op, const byte * buf, size_t len)
		{
			Broadcast(port, buf, len);
		}
		virtual void Send(uint ip, ushort port, ushort op, const byte * buf, size_t len)
		{
			Send(ip, port, buf, len);
		}
	protected:
		uint Worker();
		virtual void OnRecv(uint ip, ushort port, const byte * buf, size_t len) = 0;
	protected:
		int _socket;
		HANDLE _shutdownEvent;
		Common::Thread::Pointer _worker;
	};
}

#endif // _UDPSOCKET_H_
