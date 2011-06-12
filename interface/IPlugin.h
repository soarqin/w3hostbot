#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include "common/Singleton.h"
#include "common/Stream.h"
#include "common/SharedPtr.h"
#include "Network/TcpClient.h"
#include "Network/UdpSocket.h"

namespace Interface
{
	class IPlugin:
		public Common::SharedClass<IPlugin>
	{
	public:
		virtual ushort GetOP() = 0;
		virtual bool Process(Network::TcpClient&, Common::Stream&) = 0;
		virtual bool Process(Network::UdpSocket&, uint ip, ushort port, Common::Stream&) = 0;
	};
	class TcpPlugin:
		public IPlugin
	{
	public:
		virtual bool Process(Network::UdpSocket&, uint ip, ushort port, Common::Stream&) {return false;}
	};
	class UdpPlugin:
		public IPlugin
	{
	public:
		virtual bool Process(Network::TcpClient&, Common::Stream&) {return false;}
	};
}

#endif // _IPLUGIN_H_
