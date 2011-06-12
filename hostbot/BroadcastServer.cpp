#include "config.h"
#include "BroadcastServer.h"
#include "interface/PluginManager.h"
#include "common/Stream.h"

namespace HostBot
{
	void BroadcastServer::OnRecv( uint ip, ushort port, const byte * buf, size_t len )
	{
		if(len >= 4 && buf[0] == 0xF7 && *(ushort *)(buf + 2) <= len)
		{
		    Common::Stream st(buf + 4, len - 4);
			Interface::PluginManager::GetSingleton().Process(GetSingleton(), buf[1], ip, port, st);
		}
	}

	void BroadcastServer::Send( uint ip, ushort port, ushort op, const byte * buf, size_t len )
	{
		std::vector<byte> rbuf;
		GeneratePacket(op, buf, len, rbuf);
		Network::UdpSocket::Send(ip, port, &rbuf[0], rbuf.size());
	}

	void BroadcastServer::Broadcast( ushort port, ushort op, const byte * buf, size_t len )
	{
		std::vector<byte> rbuf;
		GeneratePacket(op, buf, len, rbuf);
		Network::UdpSocket::Broadcast(port, &rbuf[0], rbuf.size());
	}

	void BroadcastServer::GeneratePacket( ushort op, const byte * buf, size_t len, std::vector<byte>& rbuf )
	{
		rbuf.resize(4 + len);
		*(ushort *)&rbuf[0] = op;
		*(ushort *)&rbuf[2] = 4 + len;
		if(len > 0)
			memcpy(&rbuf[4], buf, len);
	}
}
