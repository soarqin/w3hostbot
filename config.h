#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef _WIN32
#ifndef WIN32
#define WIN32
#endif
#endif

#ifdef WIN32
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4146)
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "shlwapi.lib")
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif
#else
#define _WIN32_WINNT 0x0500
#endif

#include <winsock2.h>
#include <mswsock.h>
#include <windows.h>
#include <tchar.h>

#else

#endif

#undef __STRICT_ANSI__
#include <cstdio>
#include <ctime>

#include <memory>
#include <queue>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <stack>
#include <set>
#include <string>

#define ENABLE_LOG
#ifdef _DEBUG
#define LOG_LEVEL 4
#else
#define LOG_NO_VERBOSE
#endif

#ifndef byte
#define byte unsigned char
#endif
#ifndef ushort
#define ushort unsigned short
#endif
#ifndef uint
#define uint unsigned int
#endif
#ifndef uint64
#ifdef MSC_VER
#define uint64 unsigned __int64
#else
#define uint64 unsigned long long
#endif
#endif
#ifndef int64
#ifdef MSC_VER
#define int64 __int64
#else
#define int64 long long
#endif
#endif

#include "common/Log.h"

#endif // _CONFIG_H_
