#ifndef _TCPJOINGAME_H_
#define _TCPJOINGAME_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpJoinGame:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x1EF7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif // _TCPJOINGAME_H_
