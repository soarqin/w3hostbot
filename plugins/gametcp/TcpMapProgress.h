#ifndef _TCPMAPPROGRESS_H_
#define _TCPMAPPROGRESS_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpMapProgress:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x44F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif // _TCPMAPPROGRESS_H_
