#include "config.h"
#include "TcpGameSync.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotReceiver.h"

namespace Plugins
{
	namespace GameTcp
	{
		bool TcpGameSync::Process( Network::TcpClient& client, Common::Stream& st)
		{
			HostBot::Player& player = (HostBot::Player&)client;
			player.PushSync();
			return true;
		}
	}
}
