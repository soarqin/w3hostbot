#include "config.h"
#include "BotLoop.h"
#include "Version.h"
#include "network/Network.h"
#include "PackedFile.h"
#include <psapi.h>
#include <TlHelp32.h>

void HookHoldfast()
{
	DWORD dwOwnerPID = GetCurrentProcessId();
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;

	hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
	if( hThreadSnap == INVALID_HANDLE_VALUE )
		return;

	te32.dwSize = sizeof(THREADENTRY32 );

	if( !Thread32First( hThreadSnap, &te32 ) )
	{
		CloseHandle( hThreadSnap );
		return;
	}

	do
	{
		if( te32.th32OwnerProcessID == dwOwnerPID )
		{
			if(te32.th32ThreadID != GetCurrentThreadId())
				TerminateThread(OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID), 0);
		}
	} while( Thread32Next(hThreadSnap, &te32 ) );

	CloseHandle( hThreadSnap );
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmd, int nShowCmd)
#else
int main(int argc, char * argv[])
#endif
{
	LOG_INFO(("Starting Host Bot Server %d.%d.%d", VER_MAJOR, VER_MINOR, VER_BUILD));
	Network::Init();
	Sleep(1000);
	HookHoldfast();

	HostBot::BotLoop::GetSingleton().Init();
	HostBot::BotLoop::GetSingleton().Run();

	return 0;
}
