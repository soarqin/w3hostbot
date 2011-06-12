#ifndef _TCPMAPSIZE_H_
#define _TCPMAPSIZE_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpMapSize:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x42F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}


#endif // _TCPMAPSIZE_H_