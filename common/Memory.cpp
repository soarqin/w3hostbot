#include "config.h"
#include "Memory.h"
#ifdef WIN32
#include <shlwapi.h>
#endif

namespace Common
{
#ifdef WIN32
	inline void * win32_alloc(int size)
	{
		return HeapAlloc(GetProcessHeap(), 0, size);
	}

	inline void * win32_calloc(int size)
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	}

	inline void * win32_realloc(void * buf, int size)
	{
		return HeapReAlloc(GetProcessHeap(), 0, buf, size);
	}

	inline void win32_free(void * buf)
	{
		HeapFree(GetProcessHeap(), 0, buf);
	}

	inline int win32_strlena(const char * str)
	{
		return lstrlenA(str);
	}

	inline void win32_strcpya(char * dst, const char * src)
	{
		lstrcpyA(dst, src);
	}

	inline void win32_strcpyna(char * dst, const char * src, int size)
	{
		lstrcpynA(dst, src, size);
	}

	inline int win32_strcmpa(const char * s1, const char * s2)
	{
		return lstrcmpA(s1, s2);
	}

	inline int win32_strcmpia(const char * s1, const char * s2)
	{
		return lstrcmpiA(s1, s2);
	}

	inline int win32_strcmpna(const char * s1, const char * s2, int size)
	{
		return StrCmpNA(s1, s2, size);
	}

	inline int win32_strcmpnia(const char * s1, const char * s2, int size)
	{
		return StrCmpNIA(s1, s2, size);
	}

	inline char * win32_strdupa(const char * s)
	{
		int len = win32_strlena(s);
		char * ns = (char *)_MEM.Alloc(len * 2 + 2);
		if(ns == NULL)
			return NULL;
		win32_strcpya(ns, s);
		return ns;
	}
#else
	inline void * generic_alloc(int size)
	{
		return malloc(size);
	}

	inline void * generic_calloc(int size)
	{
		return calloc(1, size);
	}

	inline void * generic_realloc(void * buf, int size)
	{
		return realloc(buf, size);
	}

	inline void generic_free(void * buf)
	{
		free(buf);
	}

	inline int generic_strlena(const char * str)
	{
		return strlen(str);
	}

	inline void generic_strcpya(char * dst, const char * src)
	{
		strcpy(dst, src);
	}

	inline void generic_strcpyna(char * dst, const char * src, int size)
	{
		strncpy(dst, src, size);
	}

	inline int generic_strcmpa(const char * s1, const char * s2)
	{
		return strcmp(s1, s2);
	}

	inline int generic_strcmpia(const char * s1, const char * s2)
	{
		return stricmp(s1, s2);
	}

	inline int generic_strcmpna(const char * s1, const char * s2, int size)
	{
		return strncmp(s1, s2, size);
	}

	inline int generic_strcmpnia(const char * s1, const char * s2, int size)
	{
		return strnicmp(s1, s2, size);
	}

	inline char * generic_strdupa(const char * s)
	{
		int len = generic_strlena(s);
		char * ns = (char *)_MEM.Alloc(len * 2 + 2);
		if(ns == NULL)
			return NULL;
		generic_strcpya(ns, s);
		return ns;
	}

#endif
}
#ifdef WIN32
Common::MEM_t _MEM = {
	Common::win32_alloc,
	Common::win32_calloc,
	Common::win32_realloc,
	Common::win32_free
};

Common::STR_t _STR = {
	Common::win32_strlena,
	Common::win32_strcpya,
	Common::win32_strcpyna,
	Common::win32_strcmpa,
	Common::win32_strcmpia,
	Common::win32_strcmpna,
	Common::win32_strcmpnia,
	Common::win32_strdupa
};
#else
Common::MEM_t _MEM = {
	Common::generic_alloc,
	Common::generic_calloc,
	Common::generic_realloc,
	Common::generic_free
};

Common::STR_t _STR = {
	Common::generic_strlena,
	Common::generic_strcpya,
	Common::generic_strcpyna,
	Common::generic_strcmpa,
	Common::generic_strcmpia,
	Common::generic_strcmpna,
	Common::generic_strcmpnia,
	Common::generic_strdupa
};
#endif
