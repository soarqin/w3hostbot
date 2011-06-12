#ifndef _BOTLOOP_H_
#define _BOTLOOP_H_

#include "common/Singleton.h"

namespace HostBot
{
	class BotLoop:
		public Common::Singleton<BotLoop>
	{
	public:
		void Init();
		void Run();
	};
}

#endif // _BOTLOOP_H_