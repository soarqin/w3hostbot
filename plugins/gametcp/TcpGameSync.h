#include "interface/IPlugin.h"

namespace Plugins
{
	namespace GameTcp
	{
		class TcpGameSync:
			public Interface::TcpPlugin
		{
		public:
			virtual ushort GetOP() { return 0x27F7; }
			virtual bool Process(Network::TcpClient&, Common::Stream&);
		};
	}
}