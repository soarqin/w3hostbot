#ifndef _PLUGINMANAGER_H_
#define _PLUGINMANAGER_H_

#include "IPlugin.h"
#include "common/Singleton.h"
#include "common/Stream.h"
#include "network/TcpClient.h"
#include "network/UdpSocket.h"

namespace Interface
{
	class PluginManager:
		public Common::Singleton<PluginManager>
	{
	public:
		PluginManager();
		bool Process(Network::TcpClient& client, ushort op, Common::Stream& stream);
		bool Process(Network::UdpSocket& udp, ushort op, uint ip, ushort port, Common::Stream& stream);
		void Load(IPlugin::Pointer ptr);
	private:
		std::vector<IPlugin::Pointer> _plugins;
	};
}

#endif // _PLUGINMANAGER_H_
