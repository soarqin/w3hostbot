#ifndef _BOTGAMESET_H_
#define _BOTGAMESET_H_

#include "BotGame.h"
#include "common/Singleton.h"
#include "common/Mutex.h"

namespace HostBot
{
	class BotGameSet:
		public Common::Singleton<BotGameSet>
	{
	public:
		BotGame::Pointer operator[](uint);
		void TimerCheck(uint);
		void SendUDPInfo(uint, ushort);
		bool NewGame(std::string, std::string, MapCfg::Pointer, bool isOb);
		void RemoveGame(uint);
		std::vector<BotGame::Pointer> GetGameList();
	protected:
		static uint curGameid;
		std::map<uint, BotGame::Pointer> _games;
		Common::Mutex _locker;
	};
}

#endif // _BOTGAMESET_H_
