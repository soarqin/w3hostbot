#ifndef _TCPPONG_H_
#define _TCPPONG_H_

#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpPong:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x46F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}

#endif //_TCPPONG_H_
