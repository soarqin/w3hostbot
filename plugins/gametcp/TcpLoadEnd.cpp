#include "config.h"
#include "TcpLoadEnd.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotReceiver.h"

namespace Plugins
{
	namespace GameTcp
	{
		bool TcpLoadEnd::Process( Network::TcpClient& client, Common::Stream& )
		{
			HostBot::Player& player = (HostBot::Player&)client;
			player.LoadEnd();
			return true;
		}
	}
}
