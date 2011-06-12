#include "config.h"
#include "SysUtils.h"

namespace Common
{
	uint GetNumberOfProcessors()
	{
		static uint count = 0;
		if(count == 0)
		{
			SYSTEM_INFO si;
			GetSystemInfo(&si);
			count = si.dwNumberOfProcessors;
		}
		return count;
	}
}
