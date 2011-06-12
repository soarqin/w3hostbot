#include "config.h"
#include "BotGameSet.h"
#include "BotCfg.h"
#include "MapCfg.h"
#include "common/ScopedLock.h"

namespace HostBot
{
	uint BotGameSet::curGameid = 1;

	BotGame::Pointer BotGameSet::operator[]( uint id )
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		std::map<uint, BotGame::Pointer>::iterator it = _games.find(id);
		if(it == _games.end())
			return BotGame::Pointer();
		return it->second;
	}

	void BotGameSet::SendUDPInfo( uint ip, ushort port )
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		std::map<uint, BotGame::Pointer>::iterator it;
		for(it = _games.begin(); it != _games.end(); ++ it)
		{
			it->second->SendUDPInfo(ip, port);
		}
	}

	bool BotGameSet::NewGame( std::string gameName, std::string hostName, MapCfg::Pointer cfg, bool isOb )
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		_games[curGameid] = BotGame::Pointer(new BotGame(curGameid, gameName, hostName, cfg, BotGame::MAPSPEED_FAST, BotGame::MAPVIS_DEFAULT, isOb ? BotGame::MAPOBS_REFEREES : BotGame::MAPOBS_NONE));
		LOG_INFO(("Created game: %s", gameName.c_str()));
		++ curGameid;
		return true;
	}

	void BotGameSet::TimerCheck(uint tick)
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		std::map<uint, BotGame::Pointer>::iterator it;
		for(it = _games.begin(); it != _games.end(); ++ it)
		{
			if(it->second.get())
				it->second->TimerCheck(tick);
		}
		if(botCfg.AutoGame() && MapCfgPool::GetSingleton().GetCount() > 0)
		{
			MapCfg::Pointer cfg = MapCfgPool::GetSingleton()[botCfg.AutoDefMap()];
			if(cfg.get() == NULL)
				cfg = MapCfgPool::GetSingleton()[0];
			while(_games.size() < botCfg.AutoMaxCount())
			{
				static int counter = 0;
				++ counter;
				char numstr[128];
				sprintf(numstr, "%d", counter);
				if(!NewGame(botCfg.AutoName() + " #" + numstr, botCfg.AutoName(), cfg, cfg->GetDefaultReferee()))
					break;
			}
		}
	}

	void BotGameSet::RemoveGame( uint id )
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		_games.erase(id);
	}

	std::vector<BotGame::Pointer> BotGameSet::GetGameList()
	{
		Common::ScopedLock<Common::Mutex> lk(_locker);
		std::vector<BotGame::Pointer> result;
		std::map<uint, BotGame::Pointer>::iterator it;
		for(it = _games.begin(); it != _games.end(); ++ it)
		{
			result.push_back(it->second);
		}
		return result;
	}
}
