#include "config.h"
#include "Thread.h"

namespace Common
{
	DWORD WINAPI Thread::_Proc(LPVOID param)
	{
		Thread * th = (Thread *)param;
		return th->Proc(th->thread_param);
	}
	
	Thread::Thread( )
	{
		thread_handle = NULL;
		thread_id = 0;
	}
	
	Thread::~Thread()
	{
		if(thread_handle == NULL)
			return;
		Stop();
		thread_id = 0;
		CloseHandle(thread_handle);
	}
	
	void Thread::Start( void * param, bool pause /*= false*/ )
	{
		thread_param = param;
		thread_handle = CreateThread(NULL, 0, _Proc, (LPVOID)this, pause ? CREATE_SUSPENDED : 0, (LPDWORD)&thread_id);
		if(thread_handle == INVALID_HANDLE_VALUE || thread_handle == NULL)
		{
			thread_id = 0;
			return;
		}
	}

	void Thread::SetPriority( int prio )
	{
		switch(prio)
		{
		case IDLE:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_IDLE);
			break;
		case LOWEST:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_LOWEST);
			break;
		case LOW:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_BELOW_NORMAL);
			break;
		case NORMAL:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_NORMAL);
			break;
		case HIGH:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_ABOVE_NORMAL);
			break;
		case HIGHEST:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_HIGHEST);
			break;
		case TIME_CRITICAL:
			SetThreadPriority(thread_handle, THREAD_PRIORITY_TIME_CRITICAL);
			break;
		}
	}
	
	void Thread::Pause()
	{
		SuspendThread(thread_handle);
	}
	
	void Thread::Resume()
	{
		ResumeThread(thread_handle);
	}
	
	void Thread::Stop()
	{
		TerminateThread(thread_handle, 0);
	}
	
	bool Thread::Wait( uint millisec /*= (uint)-1*/ )
	{
		return WaitForSingleObject(thread_handle, millisec) == WAIT_OBJECT_0;
	}
}
