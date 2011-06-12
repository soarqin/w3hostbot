#include "config.h"
#include "BotLoop.h"

#include "GameServer.h"
#include "BroadcastServer.h"
#include "MapCfg.h"
#include "BotCfg.h"
#include "BotGameSet.h"
#include "common/SysTime.h"

namespace HostBot
{
	class GameTimer:
		public Network::TcpServer::ITimer
	{
	public:
		GameTimer(BotLoop * l): loop(l) {}
		virtual bool operator()()
		{
			BotGameSet::GetSingleton().TimerCheck(Common::GetTicks());
			return true;
		}
	private:
		BotLoop * loop;
	};

	class PlayerTimer:
		public Network::TcpServer::ITimer
	{
	public:
		PlayerTimer(BotLoop * l): loop(l) {}
		virtual bool operator()()
		{
			PlayerPool::GetSingleton().TimerCheck(Common::GetTicks());
			return true;
		}
	private:
		BotLoop * loop;
	};

	void BotLoop::Init()
	{
		botCfg.Load("hostbot.xml");
		LOG_DEBUG(("Loaded xml"));
		BroadcastServer::GetSingleton().Init(botCfg.UdpPort());
		GameServer::GetSingleton().Init(botCfg.TcpPort());
		LOG_DEBUG(("Network initialized"));
	}

	void BotLoop::Run()
	{
		static GameTimer gametimer(this);
		GameServer::GetSingleton().RegisterTimer(100, &gametimer);

		static PlayerTimer playertimer(this);
		GameServer::GetSingleton().RegisterTimer(1000, &playertimer);

		GameServer::GetSingleton().Run();
		while(1)
		{
			Sleep(500);
		}
	}
}
