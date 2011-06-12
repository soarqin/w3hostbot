#ifndef _THREAD_H_
#define _THREAD_H_

#include <windows.h>
#include <memory>
#include "SharedPtr.h"

namespace Common
{
	class Thread:
		public Common::SharedClass<Thread>
	{
	public:
		enum ThreadPriority
		{
			IDLE = -3,
			LOWEST = -2,
			LOW = -1,
			NORMAL = 0,
			HIGH = 1,
			HIGHEST = 2,
			TIME_CRITICAL = 3
		};
		Thread();
		virtual ~Thread();
		void Start(void * param, bool pause = false);
		void SetPriority(int prio);
		void Pause();
		void Resume();
		void Stop();
		inline uint GetId() {return thread_id;}
		bool Wait(uint millisec = (uint)-1);
	protected:
		uint thread_id;
		HANDLE thread_handle;
		void * thread_param;
		static DWORD WINAPI _Proc(LPVOID param);
		virtual uint Proc(void *) = 0;
	};
}

#endif // _THREAD_H_
