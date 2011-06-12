#ifndef _GAMESERVER_H_
#define _GAMESERVER_H_

#include "network/TcpClient.h"
#include "network/TcpServer.h"
#include "common/Singleton.h"

namespace HostBot
{
	class GameServer:
		public Common::Singleton<GameServer>,
		public Network::TcpServer
	{
	public:
	protected:
		virtual Network::TcpClient * OnNewClient(int sock);
		virtual void OnDisconnect(int);
	};
}

#endif // _GAMESERVER_H_
