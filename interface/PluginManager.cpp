#include "config.h"
#include "PluginManager.h"

namespace Interface
{
	PluginManager::PluginManager()
	{
		_plugins.resize(65536);
	}

	void PluginManager::Load( IPlugin::Pointer ptr )
	{
		ushort op = ptr->GetOP();
		if(op < _plugins.size())
			_plugins[op] = ptr;
	}

	bool PluginManager::Process( Network::TcpClient& client, ushort op, Common::Stream& stream )
	{
		IPlugin * plugin = _plugins[op].get();
		if(plugin == NULL)
		{
			LOG_INFO(("Received unknown op code: %04X", op));
			return false;
		}
		return plugin->Process(client, stream);
	}

	bool PluginManager::Process( Network::UdpSocket& udp, ushort op, uint ip, ushort port, Common::Stream& stream )
	{
		IPlugin * plugin = _plugins[op].get();
		if(plugin == NULL)
			return false;
		return plugin->Process(udp, ip, port, stream);
	}
}
