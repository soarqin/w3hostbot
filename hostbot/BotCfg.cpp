#include "config.h"
#include "BotCfg.h"
#include "MapCfg.h"
#include "text/XmlConfig.h"

namespace HostBot
{
	BotCfg botCfg;
	void BotCfg::Load( const char * filename )
	{
		LOG_INFO(("Loading config."));
		Text::XmlConfig config(filename);

		_password = config.GetString("Admin", "Password", "12345");

		_saveReplay = config.GetInteger("Game", "SaveReplay", 0) > 0;
		_syncLimit = config.GetInteger("Game", "SyncLimit", 40);
		_gameVersion = config.GetInteger("Game", "Version", 24);

		_autoGame = config.GetInteger("Auto", "Enable", 0) > 0;
		_autoName = config.GetString("Auto", "Name", "Host Bot");
		_autoMaxCount = config.GetInteger("Auto", "MaxCount", 5);
		_autoDefMap = config.GetString("Auto", "DefaultMap", "");

		_tcpPort = config.GetInteger("Network", "TcpPort", 6112);
		_udpPort = config.GetInteger("Network", "UdpPort", 6112);

		_scriptPath = config.GetString("Scripts", "Path", "Scripts");
		if(!_scriptPath.empty() && _scriptPath[_scriptPath.size() - 1] != '\\')
			_scriptPath += '\\';

		std::vector<std::vector<std::string> > mapcfgset;
		std::vector<std::string> keys;
		keys.push_back("Name");
		keys.push_back("Path");
		keys.push_back("FakePath");
		keys.push_back("MinStartCount");
		keys.push_back("Referee");
		config.ReadArray(mapcfgset, keys, "Maps", "Map");
		for(size_t i = 0; i < mapcfgset.size(); ++ i)
		{
			MapCfgPool::GetSingleton().Add(MapCfg::Pointer(new MapCfg(mapcfgset[i][0].c_str(), mapcfgset[i][1].c_str(), mapcfgset[i][2].c_str(), atoi(mapcfgset[i][3].c_str()), atoi(mapcfgset[i][4].c_str()) > 0)));
		}
	}
}
