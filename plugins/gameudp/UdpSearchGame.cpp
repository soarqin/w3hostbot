#include "config.h"
#include "UdpSearchGame.h"
#include "hostbot/BotGameSet.h"
#include "hostbot/BotCfg.h"

bool Plugins::GameUdp::UdpSearchGame::Process( Network::UdpSocket&, uint ip, ushort port, Common::Stream& in )
{
	uint platform, version;
	in>>platform>>version;
	if(platform != 'W3XP' || version != HostBot::botCfg.GameVersion())
		return false;
	HostBot::BotGameSet::GetSingleton().SendUDPInfo(ip, port);
	return true;
}
