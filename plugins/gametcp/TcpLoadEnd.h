#ifndef _TCPLOADEND_H_
#define _TCPLOADEND_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpLoadEnd:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x23F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif // _TCPLOADEND_H_
