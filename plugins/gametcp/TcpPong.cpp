#include "config.h"
#include "TcpPong.h"
#include "common/SysTime.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotReceiver.h"

namespace Plugins
{
	namespace GameTcp
	{
		bool TcpPong::Process( Network::TcpClient& client, Common::Stream& in)
		{
			if(in.left() < 4)
				return false;
			uint tick;
			in>>tick;

			HostBot::Player& player = (HostBot::Player&)client;

			player.SetPing(Common::GetTicks() - tick);
			return true;
		}
	}
}
