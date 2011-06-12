#ifndef _UDPSEARCHGAME_H_
#define _UDPSEARCHGAME_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameUdp
	{
		class UdpSearchGame:
			public Interface::UdpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x2F; }
			virtual bool Process(Network::UdpSocket&, uint, ushort, Common::Stream&);
		};
	}
}

#endif // _UDPSEARCHGAME_H_
