#ifndef _TCPGAMEACTION_H_
#define _TCPGAMEACTION_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpGameAction:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x26F7; }
			virtual bool Process(Network::TcpClient& client, Common::Stream&);
		};
	}
}

#endif // _TCPGAMEACTION_H_
