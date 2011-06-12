#ifndef _TCPCHAT_H_
#define _TCPCHAT_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpChat:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x28F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif // _TCPCHAT_H_
