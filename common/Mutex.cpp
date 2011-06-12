#include "Config.h"
#include "PreConfig.h"
#include "Mutex.h"


#if defined(_WIN32)
#include "Mutex_WIN32.cpp"
#else
#include "Mutex_POSIX.cpp"
#endif


namespace Common {


Mutex::Mutex()
{
}


Mutex::~Mutex()
{
}


FastMutex::FastMutex()
{
}


FastMutex::~FastMutex()
{
}


} // namespace Common
