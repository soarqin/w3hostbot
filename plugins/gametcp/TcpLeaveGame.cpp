#include "config.h"
#include "TcpLeaveGame.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotReceiver.h"

namespace Plugins
{
	namespace GameTcp
	{
		bool TcpLeaveGame::Process( Network::TcpClient& client, Common::Stream& in )
		{
			uint reason;
			in>>reason;

			HostBot::Player& player = (HostBot::Player&)client;
			player.SetLeaveReason(7);
			player.LeaveGame();
			return true;
		}
	}
}
