#ifndef _TCPLEAVEGAME_H_
#define _TCPLEAVEGAME_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpLeaveGame:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x21F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif // _TCPLEAVEGAME_H_
