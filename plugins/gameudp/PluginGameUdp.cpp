#include "config.h"
#include "PluginGameUdp.h"
#include "UdpSearchGame.h"

namespace Plugins
{
	namespace GameUdp
	{
		PLUGIN_BEGIN(PluginGameUdp)
			PLUGIN_ADD(UdpSearchGame)
		PLUGIN_END()
	}
}
