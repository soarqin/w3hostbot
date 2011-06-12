#include "config.h"
#include "GameServer.h"
#include "Player.h"

namespace HostBot
{
	Network::TcpClient * GameServer::OnNewClient( int fd )
	{
		return new Player(fd);
	}

	void GameServer::OnDisconnect( int fd )
	{
		Network::TcpClient::Pointer ptr = GetClient(fd);
		if(ptr.get() == 0)
			return;
		HostBot::Player* player = (HostBot::Player*)ptr.get();
		player->SetLeaveReason(1);
		player->LeaveGame();
	}
}
