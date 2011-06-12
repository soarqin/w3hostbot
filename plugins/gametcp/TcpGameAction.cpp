#include "config.h"
#include "TcpGameAction.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotReceiver.h"

namespace Plugins
{
	namespace GameTcp
	{
		bool TcpGameAction::Process( Network::TcpClient& client, Common::Stream& st)
		{
			if(st.size() <= 4)
				return true;
			HostBot::Player& player = (HostBot::Player&)client;
			player.PushAction(((byte *)st) + 4, st.size() - 4);
			return true;
		}
	}
}
